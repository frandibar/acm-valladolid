/* @JUDGE_ID:  40922FK  10067  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10067 - Playing with Wheels
 by: Francisco Dibar
 date: Aug-16-2005
**************************************************************************/

//#define DEBUG 
//#define ONLINE_JUDGE 
#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <algorithm>        // sort, binary_search

#ifdef DEBUG
    #define START_DEBUG "START DEBUG ********************************************************************\n"
    #define END_DEBUG   "END DEBUG **********************************************************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

using std::cin;
using std::cout;
using std::endl;

/**************************************************************************
 GRAPH Library Header
 by: Francisco Dibar
 date: Aug-09-2006
 include libraries: list, map, string, vector, queue
TODO: finish dijkstra
**************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <list>
#include <map>
#include <string>
#include <vector>
#include <queue>

using std::string;
using std::map;
using std::list;
using std::vector;
using std::queue;
using std::pair;

#include <iostream> // TODO: remove
using std::cout;    // TODO: remove
using std::cin;     // TODO: remove
using std::endl;     // TODO: remove

///////////////////////////////////////////////////////////////////////////
class Edge {

public:
    // constructor
    Edge(int d, int w) : destiny_(d), weight_(w) {}
    
    // getters
    inline int getDestiny() const { return destiny_; }
    inline int getWeight() const { return weight_; }
    
    // setters
    inline void setDestiny(int d) { destiny_ = d; }
    inline void setWeight(int w) { weight_ = w; }

    void process() {};

private:
    int destiny_;
    int weight_;
};

///////////////////////////////////////////////////////////////////////////
class Vertex {

public:
    // constructor
    Vertex(const string& name = "") : name_(name) {}

    // getters
    inline string getName() const { return name_; }
    inline int getDistance() const { return distance_; }
    inline int getPrevious() const { return previous_; }
    inline int getExtra() const { return extra_; }
    inline int getEdgeCount() const { return adyList_.size(); }
    inline list<Edge>& getAdyList() { return adyList_; }        // TODO: should be const

    // setters
    inline void setName(const string& aName) { name_ = aName; }
    inline void setDistance(int aDistance) { distance_ = aDistance; }
    inline void setPrevious(int aPrevious) { previous_ = aPrevious; }
    inline void setExtra(int aExtra) { extra_ = aExtra; }
    inline void setAdyList(list<Edge>& aList) { adyList_ = aList; }

    void process();

private:
    string name_;           // vertex real name
    list<Edge> adyList_;    // adjacency list, where edges are inserted
    int distance_;          // weight (after performing algorithm)
    int previous_;          // previous vertex in minimum path
    int extra_;             // extra variable used in algorithms
};

// Type for pointer to function whose argument is a pointer to void.
// Should be user defined, and will be applied when visiting vertex.
typedef void (*PROC_VERT_VISIT)(void *);

///////////////////////////////////////////////////////////////////////////
class Graph {

public:
    // constructor
    Graph(bool directed = false) : directed_(directed), nVertexes_(0), nEdges_(0) {}
    
    // getters
    int getEdgeCount() { return nEdges_; }
    int getVertexCount() { return nVertexes_; }

    // traversing
    void bfs(const string&);
    inline void dfs(const string&);
    void minPathNoWeight(const string&);
    void showPath(const string&);
    void show();

    void addEdge(const string&, const string&, int);
    bool addVertex(const string&);

    inline void setProcess(PROC_VERT_VISIT fn) { procVisitVertex_ = fn; }
    int maximumConnectedSubgraphs();
    bool convex() { return (maximumConnectedSubgraphs() == 1); }
    bool vertexExists(const string&);

protected:
    bool addInternalEdge(int, int, int);
    int addVertexToDiccionary(const string&, bool*);
    void clear();
    bool dijkstra(int);
    void dfs(int);

    void printPathRec(int);

private:
    bool directed_;
    map<string, int> mapVertexes_;   // links vertex number with name
    vector<Vertex> vTable_;
    int nVertexes_;
    int nEdges_;
    // pointer to function that applies on visited vertex
    PROC_VERT_VISIT procVisitVertex_;
};

///////////////////////////////////////////////////////////////////////////

#endif  // GRAPH_H_INCLUDED


/**************************************************************************
 GRAPH Library Implementation
 by: Francisco Dibar
 date: Aug-09-2006
**************************************************************************/

const long INFINITY = 715827882;    //  2147483647 / 3  //  maxint/3
const int NULL_VERTEX = -1;


///////////////////////////////////////////////////////////////////////////
void Graph::addEdge(const string& aOrigin, const string& aDestiny, int aWeight = 1)
{
    // add vertexes if they don't exist
    addVertex(aOrigin);
    addVertex(aDestiny);

    // get vertex indexes from hash table
    int orig = mapVertexes_[aOrigin];
    int dest = mapVertexes_[aDestiny];

    addInternalEdge(orig, dest, aWeight);
    if (!directed_) 
        // add edge going on the other direction
        addInternalEdge(dest, orig, aWeight);

}

///////////////////////////////////////////////////////////////////////////
bool Graph::addInternalEdge(int aOrigin, int aDestiny, int aWeight)
// add edge, if it exists then weight is modified, else return true    
{
    list<Edge>::iterator li;
    bool found = false;

    // find edge in list
    for (li = vTable_[aOrigin].getAdyList().begin(); 
                    !found && (li != vTable_[aOrigin].getAdyList().end()); ++li) {
        Edge &ed = *li;
        if (ed.getDestiny() == aDestiny) {
            ed.setWeight(aWeight);
            found = true;
        }
    }
    if (!found) {
        // add Edge
        (vTable_[aOrigin].getAdyList()).push_back(Edge(aDestiny, aWeight));
        nEdges_++;
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool Graph::addVertex(const string& aName)
// si el Vertex no existe en el grafo, lo agrega y devuelve true
{
    bool notExists;
    addVertexToDiccionary(aName, &notExists);
    // agregar el Vertex al grafo si no existe
    if (notExists) {     
        vTable_.push_back(Vertex(aName));
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
int Graph::addVertexToDiccionary(const string& aName, bool *notExists)
// if aName already exists, then return internal number, if not add to dictionary    
{
    // duplicate keys not allowed, if it already exists then it is no inserted
    typedef map<string, int>::iterator mi;
    pair<mi, bool> res; 
    // insert returns pair(iterador, bool) with bool = true if inserted and false if already existed
    res = mapVertexes_.insert(map<string, int>::value_type(aName, nVertexes_));
    if (res.second) {   // indicates if added or not
        nVertexes_++;
        *notExists = true;
    } else
        *notExists = false;
    
    return mapVertexes_[aName];
}

///////////////////////////////////////////////////////////////////////////
void Graph::bfs(const string& aFromVertex)
{
    int idVertexFrom = mapVertexes_[aFromVertex];

    // I use vTable_.size() instead of nVertexes_ because if vertexes are eliminated
    // maybe idVertex > nVertexes_
    vector<bool> processed(vTable_.size()); 
    vector<bool> discovered(vTable_.size());
    vector<int> parent(vTable_.size());

    queue<int> q;
    q.push(idVertexFrom);
    discovered[idVertexFrom] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        vTable_[v].process();
        processed[v] = true;
        // traverse vertex v's edge list
        list<Edge>::const_iterator LI;
        for (LI = vTable_[v].getAdyList().begin(); 
                LI != vTable_[v].getAdyList().end(); LI++) {
            int w = (*LI).getDestiny();
            if (!discovered[w]) {
                q.push(w);
                discovered[w] = true;
                parent[w] = v;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void Graph::minPathNoWeight(const string& vertOrigen)
{
    queue<int> q;

    int nroVertOrigen = mapVertexes_[vertOrigen];
    clear();
    vTable_[nroVertOrigen].setDistance(0);
    q.push(nroVertOrigen);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        list<Edge>& getAdyList = vTable_[v].getAdyList();
        list<Edge>::iterator li;
        for (li = getAdyList.begin(); 
                li != getAdyList.end(); ++li) {
            Edge &ar = *li;
            int w = ar.getDestiny();
            if (vTable_[w].getDistance() == INFINITY) {
                vTable_[w].setDistance(vTable_[v].getDistance() + 1); 
                vTable_[w].setPrevious(v); 
                q.push(w);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
inline void Graph::dfs(const string& aFromVertex)
{
    int idFromVertex = mapVertexes_[aFromVertex];
    dfs(idFromVertex);
}

///////////////////////////////////////////////////////////////////////////
void Graph::dfs(int idFromVertex)
{
    // I use vTable_.size() instead of nVertexes_ because if vertexes are eliminated
    // maybe idVertex > nVertexes_
    vector<bool> processed(vTable_.size()); 
    vector<bool> discovered(vTable_.size());
    vector<int> parent(vTable_.size());

    discovered[idFromVertex] = true;
    vTable_[idFromVertex].process();

    list<Edge>::iterator LI;        // const
    for (LI = vTable_[idFromVertex].getAdyList().begin(); 
            LI != vTable_[idFromVertex].getAdyList().end(); LI++) {
        int w = (*LI).getDestiny();
        if (!discovered[w]) {
            parent[w] = idFromVertex;
            dfs(w);
        } else 
            if (!processed[w])
                vTable_[w].process();
    }
    processed[idFromVertex] = true;
}


///////////////////////////////////////////////////////////////////////////
bool Graph::dijkstra(int vertOrigen)
// TODO:
{
/*  LimpiarDatos();
//  priority_queue<int, int> pq;
    priority_queue<Vertex, less<Vertex> > pq;
    vTable_[vertOrigen].Distancia() = 0;
    //pq.push(priority_queue<Vertex, less<Vertex> >::value_type(vertOrigen, 0));
    pq.push(vTable_[vertOrigen]);
*/
/*
    int v, w;
    CColaPrioridad cp;
    CElementoCola vrec(NULL_VERTEX);
    CVertex *pVertex = (CVertex *)vTable_->ElementAt(nodoOrigen);

    LimpiarDatos();
    pVertex->Distancia() = 0;
    cp.Insertar(new CElementoCola(nodoOrigen, 0));

    for (int nodosVistos = 0; nodosVistos < nVertexes_; nodosVistos++) {
        do {
            if (cp.Vacia())
                return;
            vrec.Destino() = cp.EliminarMin();
            pVertex = (CVertex *)vTable_->ElementAt(vrec.Destino());
        } while (pVertex->Conocido() == false);
        
        v = vrec.Destino();
        pVertex = (CVertex *)vTable_->ElementAt(v);
        pVertex->Conocido() = true;

        CObList *pLista = new CObList;
        // copiar la lista de adyacencia para el Vertex v en pLista
        pLista->AddHead(pVertex->ObtenerLista());

        POSITION pos = pLista->GetHeadPosition();
        for ( ; pos != NULL ; pLista->GetNext(pos)) {
            w = ((CEdge *)pLista->GetAt(pos))->Destino();
            int cvw = ((CEdge *)pLista->GetAt(pos))->Costo();
            CVertex *pVertexW = (CVertex *)vTable_->ElementAt(w);
            
            if (cvw < 0) {
                cerr << "\nError al hallar el camino minimo, no se aceptan Edges negativas\n";
                return;
            }

            if (pVertexW->Distancia() > pVertex->Distancia() + cvw) {
                pVertexW->Distancia() = (pVertex->Distancia() + cvw);
                pVertexW->Anterior() = v; 
                cp.Insertar(new CElementoCola(w, pVertexW->Distancia()));
            }
        }
    }
*/  return false;
}

///////////////////////////////////////////////////////////////////////////
bool Graph::vertexExists(const string& aName)
{
    map<string, int>::const_iterator iter;
    iter = mapVertexes_.find(aName);
    return (iter != mapVertexes_.end());
}

///////////////////////////////////////////////////////////////////////////
void Graph::showPath(const string& aFromVertex)
{
    int idToVertex = mapVertexes_[aFromVertex];
    if (vTable_[idToVertex].getDistance() == INFINITY)
        cout << vTable_[idToVertex].getName() << " is unreachable" << endl;
    else {
        printPathRec(idToVertex);
        cout << "The weight is " << vTable_[idToVertex].getDistance() << endl;
    }
}

///////////////////////////////////////////////////////////////////////////
void Graph::printPathRec(int toVertex)
{
    if (vTable_[toVertex].getPrevious() != NULL_VERTEX) {
        printPathRec(vTable_[toVertex].getPrevious());
        cout << " to ";
    }
    cout << vTable_[toVertex].getName();
}

///////////////////////////////////////////////////////////////////////////
void Graph::clear()
// initialize minimum path table    
{
    vector<Vertex>::iterator vi;
    for (vi = vTable_.begin(); vi != vTable_.end(); ++vi) {
        Vertex &vert = *vi;
        vert.setDistance(0);
        vert.setPrevious(NULL_VERTEX);
        vert.setExtra(0);
    }
}

///////////////////////////////////////////////////////////////////////////
int Graph::maximumConnectedSubgraphs()
// returns maximum amount of convex subgraphs
// observation: maybe different values are returned if graph is directed or not    
{
    int max = 0;
    vector<bool> vec_vistos(vTable_.size());

    // bfs
    vector<bool> discovered(vTable_.size());

    // TODO: what happens if vertex i doesn't exist?
    for (int i = 0; i < (int)vTable_.size(); i++) {
        if (!discovered[i]) {
            queue<int> q;
            q.push(i);
            discovered[i] = true;
            max++;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                // traverse vertex v's adjacency list
                list<Edge>::iterator LI;        // const
                for (LI = vTable_[v].getAdyList().begin(); 
                        LI != vTable_[v].getAdyList().end(); LI++) {
                    int w = (*LI).getDestiny();
                    if (!discovered[w]) {
                        q.push(w);
                        discovered[w] = true;
                    }
                }
            }
        } 
    }

    return max;
}

///////////////////////////////////////////////////////////////////////////
void Graph::show()
{
    cout << (directed_ ? "Directed" : "Non Directed") << " Graph "
        << ": " << endl << endl;
    cout << "Vertexes (" << nVertexes_ << "):" << endl << endl;
    for (int i = 0; i < nVertexes_; i++)
        cout << vTable_[i].getName() << endl;
        
    cout << endl;
    cout << "Edges (" << nEdges_ << "):" << endl;
    cout << "[Origin Vertex] -> [Destiny Vertex]: [Weight]" << endl << endl;

    for (int i = 0; i < nVertexes_; i++) {
        Vertex &vert = vTable_[i];
        list<Edge> &ar = vert.getAdyList();

        list<Edge>::iterator li;
        for (li = ar.begin(); li != ar.end(); ++li)
            cout << vert.getName() << "\t->\t" 
                << vTable_[(*li).getDestiny()].getName() 
                << ":\t" << (*li).getWeight() << endl;
    }
}

///////////////////////////////////////////////////////////////////////////
void Vertex::process()
{
    cout << name_ << endl;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


const int L1 = 0;
const int R1 = 1;
const int L2 = 2;
const int R2 = 3;
const int L3 = 4;
const int R3 = 5;
const int L4 = 6;
const int R4 = 7;

const int NWHEELS = 4;
const int NMOVES = 8;           // 2 * NWHEELS
const int NSTATES = 10000;      // NWHEELS * ...
const int NOT_REACHABLE = -1;

///////////////////////////////////////////////////////////////////////////
string toString(int n)
{
	string s(4, '0');
	s[0] = (n / 1000) + '0';
	s[1] = ((n / 100) % 10) + '0';
	s[2] = ((n / 10) % 10) + '0';
	s[3] = n % 10 + '0';
    return s;
}

///////////////////////////////////////////////////////////////////////////
inline int buildState(int a, int b, int c, int d)
{
    return a * 1000 + b * 100 + c * 10 + d;
}

///////////////////////////////////////////////////////////////////////////
inline int left(int n)
{
    return (n == 0) ? 9 : n-1;
}

///////////////////////////////////////////////////////////////////////////
inline int right(int n)
{
    return (n == 9) ? 0 : n+1;
}

///////////////////////////////////////////////////////////////////////////
int nextState(int state, int move)
{
    int next = state;
    int a, b, c, d;
    a = state / 1000;
    b = (state / 100) % 10;
    c = (state / 10) % 10;
    d = state % 10;
    switch (move) {
        case L1: next = buildState(left(a), b, c, d);  break; 
        case R1: next = buildState(right(a), b, c, d); break;
        case L2: next = buildState(a, left(b), c, d);  break;
        case R2: next = buildState(a, right(b), c, d); break;
        case L3: next = buildState(a, b, left(c), d);  break;
        case R3: next = buildState(a, b, right(c), d); break;
        case L4: next = buildState(a, b, c, left(d));  break;
        case R4: next = buildState(a, b, c, right(d)); break;
        default: break;
    }
    return next;
}


///////////////////////////////////////////////////////////////////////////
int nsteps(Graph& g, const vector<int>& vForbidden, int initial, int target)
// return number of steps from initial to target, without passing
// through forbidden states
// precondition: vForbidden must be sorted
{
    if (initial == target)
        return 0;

    queue<int>   qStates;
    vector<bool> vDiscovered(NSTATES);
    vector<int>  vParent(NSTATES);

    qStates.push(initial);
    int v = qStates.front();
    // do a bfs, adding vertices to qStates
    while (!qStates.empty() && (v != target)) {

#ifdef DEBUG
        cout << v << endl;
#endif
        vDiscovered[v] = true;
        qStates.pop();
        for (int m = 0; m < NMOVES; ++m) {
            int n = nextState(v, m);
            if (!vDiscovered[n] && !std::binary_search(vForbidden.begin(), vForbidden.end(), n)) {
                vDiscovered[n] = true;
                g.addEdge(toString(v), toString(n));
                qStates.push(n);
                vParent[n] = v;
            }
        }
        if (!qStates.empty())
            v = qStates.front();
    }

#ifdef DEBUG
    cout << "Showing Target to Initial states:" << endl;
    cout << v << endl;
#endif

    // go all the way up and count the distance
    if (v == target) {
        int distance = 1;
        while (vParent[v] != initial) {

#ifdef DEBUG
            cout << vParent[v] << endl;
#endif
            distance++;
            v = vParent[v];
        }

#ifdef DEBUG
        cout << vParent[v] << endl;
#endif
        return distance;
    } else
        return NOT_REACHABLE;
}


///////////////////////////////////////////////////////////////////////////
//	MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// redirect input and output
	#ifndef ONLINE_JUDGE 
		cin.rdbuf((new std::ifstream("input"))->rdbuf()); 
		cout.rdbuf((new std::ofstream("output"))->rdbuf()); 
	#endif 

    int cases;
    cin >> cases;
    for (int k = 0; (k < cases) && (!cin.eof()); ++k) {
        // READ INPUT
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int initial = buildState(a, b, c, d);
        cin >> a >> b >> c >> d;
        int target = buildState(a, b, c, d);
        int nforbidden;
        cin >> nforbidden;
        vector<int> vForbidden(nforbidden);
        for (int m = 0; m < nforbidden; ++m) {
            cin >> a >> b >> c >> d;
            vForbidden[m] = buildState(a, b, c, d);
        }
        std::sort(vForbidden.begin(), vForbidden.end());

#ifdef DEBUG
        cout << START_DEBUG;
#endif
        // PROCESS AND SHOW OUTPUT
        Graph g(true);  // directed graph
        int n = nsteps(g, vForbidden, initial, target);
#ifdef DEBUG
        //cout << "edges: " << g.getEdgeCount() << endl;
        //cout << "vertexes " << g.getVertexCount() << endl;
        //g.show();
        cout << END_DEBUG;
#endif
        cout << n << endl;
    }
    return 0;
}

/* @END_OF_SOURCE_CODE */

