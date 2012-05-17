/* @JUDGE_ID:  40922FK  10044  C++  */
/* @BEGIN_OF_SOURCE_CODE */    
/**************************************************************************
 Solution to Problem 10044 - Erdos Numbers
 by: Francisco Dibar
 date: Aug-21-2006
**************************************************************************/

//#define DEBUG 
//#define ONLINE_JUDGE 

#ifdef DEBUG
    #define START_DEBUG	"**************************** START DEBUG *****************************\n"
    #define END_DEBUG	"***************************** END DEBUG ******************************\n"
    // g++-2.95 doesn't support asserts
    #define ASSERT(x,y)   if (!(x)) { std::cerr << "ASSERTION FAILED!: " << y << "\n"; exit(1); }
#endif

#include <iostream>
#ifndef ONLINE_JUDGE 
    #include <fstream>
#endif 
#include <string>

const char* ERDOS = "Erdos, P.";

/**************************************************************************
 GRAPH Library Header
 by: Francisco Dibar
 date: Aug-09-2006
 include libraries: list, map, queue, string, vector
TODO: finish dijkstra
**************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <sstream>

using std::list;
using std::map;
using std::pair;
using std::queue;
using std::string;
using std::vector;

///////////////////////////////////////////////////////////////////////////
class Edge {

public:
    // constructor
    Edge(int d, int w) : destiny_(d), weight_(w) {}
    
    // getters
    inline int getDestiny() const { return destiny_; }
    inline int getWeight()  const { return weight_; }
    
    // setters
    inline void setDestiny(int d) { destiny_ = d; }
    inline void setWeight(int w) { weight_ = w; }

private:
    int destiny_;
    int weight_;
};

///////////////////////////////////////////////////////////////////////////
class Vertex {

public:
    // constructor
    Vertex(const string& aName = "") : name_(aName) {}

    // getters
    inline string  getName()      const { return name_; }
    inline int     getDistance()  const { return distance_; }
    inline int     getPrevious()  const { return previous_; }
    inline int     getExtra()     const { return extra_; }
    inline int     getEdgeCount() const { return adyList_.size(); }
    inline list<Edge>& getAdyList() { return adyList_; }        // TODO: should be const

    // setters
    inline void setName(const string& aName) { name_ = aName; }
    // the following sets are const since mutable variables are being modified
    inline void setDistance(int aDistance) const { distance_ = aDistance; }
    inline void setPrevious(int aPrevious) const { previous_ = aPrevious; }
    inline void setExtra(int aExtra) const { extra_ = aExtra; }
    inline void setAdyList(list<Edge>& aList) { adyList_ = aList; }

private:
    string name_;           // vertex real name
    list<Edge> adyList_;    // adjacency list, where edges are inserted
    mutable int distance_;  // weight (after performing algorithm)
    mutable int previous_;  // previous vertex in minimum path
    mutable int extra_;     // extra variable used in algorithms
};

// Type for pointer to function whose argument is a reference to Vertex
// Should be user defined, and will be applied when visiting vertex.
typedef void (*PROC_VISIT_VERT)(const Vertex&);

///////////////////////////////////////////////////////////////////////////
class Graph {

public:
    // constructor
    Graph(bool directed = false) : directed_(directed), nVertexes_(0), nEdges_(0) {}
    
    // getters
    int getEdgeCount() const { return nEdges_; }
    int getVertexCount() const { return nVertexes_; }

    // traversing
    void bfs(const string&); // const;
    long shortestDistance(const string&, const string&); // const;
    inline void dfs(const string&); // const;
    void minPathNoWeight(const string&); // const;
    string showPath(const string&) const;
    inline void setProcess(PROC_VISIT_VERT fn) { procVisitVertex_ = fn; }

    // building
    void addEdge(const string&, const string&, int);
    bool addVertex(const string&);

    int maximumConnectedSubgraphs();
    inline bool isConvex() { return (maximumConnectedSubgraphs() == 1); }
    bool vertexExists(const string&) const;

    static const long INFINITY    = 715827882;    //  2147483647 / 3  //  maxint/3
    static const int  NULL_VERTEX = -1;

    friend std::ostream& operator<<(std::ostream&, /*const*/ Graph&);   // TODO

protected:
    bool addInternalEdge(int, int, int);
    int  addVertexToDiccionary(const string&, bool*);
    void clear() const;
    bool dijkstra(int);
    void dfs(int);

    string printPathRec(int) const;

private:
    bool directed_;                     // directed or undirected graph
    map<string, int> mapVertexes_;      // links vertex number with name
    vector<Vertex> vTable_;             // stores vertexes
    int nVertexes_;                     // # of vertexes
    int nEdges_;                        // # of edges
    PROC_VISIT_VERT procVisitVertex_;   // pointer to function that applies on visited vertex
};

///////////////////////////////////////////////////////////////////////////

#endif  // GRAPH_H_INCLUDED


/**************************************************************************
 GRAPH Library Implementation
 by: Francisco Dibar
 date: Aug-09-2006
**************************************************************************/

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
// if vertex doesn't exist, adds it and returns true    
{
    bool notExists;
    addVertexToDiccionary(aName, &notExists);
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
long Graph::shortestDistance(const string& aFromVertex, const string& aToVertex) //const
// returns shortest distance from aFromVertex to aToVertex    
// precondition: procVisitVertex_ is valid    
{
    if (aFromVertex == aToVertex)
        return 0;

    // applies bfs
    int idFromVertex = mapVertexes_.find(aFromVertex)->second; // mapVertexes_[aFromVertex] isn't const
    int idToVertex = mapVertexes_.find(aToVertex)->second;

    // I use vTable_.size() instead of nVertexes_ because if vertexes are eliminated
    // maybe idVertex > nVertexes_
    vector<bool> vProcessed(vTable_.size());  // stores visited and processed vertexes
    vector<bool> vDiscovered(vTable_.size()); // stores discovered but not processed vertexes
    vector<int> vParent(vTable_.size());

    queue<int> q;
    q.push(idFromVertex);
    vDiscovered[idFromVertex] = true;
    int v = idFromVertex;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        vProcessed[v] = true;
        // traverse vertex v's edge list
        list<Edge>::const_iterator li;
        for (li = vTable_[v].getAdyList().begin(); li != vTable_[v].getAdyList().end(); ++li) {
            int w = (*li).getDestiny();
            if (!vDiscovered[w]) {
                vDiscovered[w] = true;
                vParent[w] = v;
                if (w == idToVertex) {
                    // build the way up from aToVertex to aFromVertex using vParent
                    long dist = 1;
                    while (vParent[w] != idFromVertex) {
                        dist++;
                        w = vParent[w];
                    }
                    return dist;
                }
                q.push(w);
            }
        }
    }
    return INFINITY;
}

///////////////////////////////////////////////////////////////////////////
void Graph::bfs(const string& aFromVertex) //const
// precondition: procVisitVertex_ is valid    
{
    //int idFromVertex = mapVertexes_[aFromVertex];
    int idFromVertex = mapVertexes_.find(aFromVertex)->second; // mapVertexes_[aFromVertex] isn't const

    // I use vTable_.size() instead of nVertexes_ because if vertexes are eliminated
    // maybe idVertex > nVertexes_
    vector<bool> vProcessed(vTable_.size()); 
    vector<bool> vDiscovered(vTable_.size());
    vector<int> vParent(vTable_.size());

    queue<int> q;
    q.push(idFromVertex);
    vDiscovered[idFromVertex] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        procVisitVertex_(vTable_[v]);
        vProcessed[v] = true;
        // traverse vertex v's edge list
        list<Edge>::const_iterator li;
        for (li = vTable_[v].getAdyList().begin(); li != vTable_[v].getAdyList().end(); ++li) {
            int w = (*li).getDestiny();
            if (!vDiscovered[w]) {
                q.push(w);
                vDiscovered[w] = true;
                vParent[w] = v;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void Graph::minPathNoWeight(const string& originVertex)
{
    queue<int> q;

    int idOriginVertex = mapVertexes_[originVertex];
    clear();
    vTable_[idOriginVertex].setDistance(0);
    q.push(idOriginVertex);
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
// precondition: procVisitVertex_ is valid    
{
    // I use vTable_.size() instead of nVertexes_ because if vertexes are eliminated
    // maybe idVertex > nVertexes_
    vector<bool> vProcessed(vTable_.size()); 
    vector<bool> vDiscovered(vTable_.size());
    vector<int> vParent(vTable_.size());

    vDiscovered[idFromVertex] = true;
    procVisitVertex_(vTable_[idFromVertex]);

    list<Edge>::const_iterator li;
    for (li = vTable_[idFromVertex].getAdyList().begin(); 
            li != vTable_[idFromVertex].getAdyList().end(); ++li) {
        int w = (*li).getDestiny();
        if (!vDiscovered[w]) {
            vParent[w] = idFromVertex;
            dfs(w);
        } else if (!vProcessed[w])
            procVisitVertex_(vTable_[w]);
    }
    vProcessed[idFromVertex] = true;
}


///////////////////////////////////////////////////////////////////////////
bool Graph::dijkstra(int originVertex)
// TODO:
{
/*  clear();
//  priority_queue<int, int> pq;
    priority_queue<Vertex, less<Vertex> > pq;
    vTable_[originVertex].Distancia() = 0;
    //pq.push(priority_queue<Vertex, less<Vertex> >::value_type(originVertex, 0));
    pq.push(vTable_[originVertex]);
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
bool Graph::vertexExists(const string& aName) const
{
    map<string, int>::const_iterator mi;
    mi = mapVertexes_.find(aName);
    return (mi != mapVertexes_.end());
}

///////////////////////////////////////////////////////////////////////////
string Graph::showPath(const string& aFromVertex) const
{
    std::ostringstream os;
    int idToVertex = mapVertexes_.find(aFromVertex)->second; // mapVertexes_[aFromVertex] isn't const
    if (vTable_[idToVertex].getDistance() == INFINITY)
        os << vTable_[idToVertex].getName() << " is unreachable" << std::endl;
    else {
        os << printPathRec(idToVertex);
        os << "The weight is " << vTable_[idToVertex].getDistance() << std::endl;
    }
    return os.str();
}

///////////////////////////////////////////////////////////////////////////
string Graph::printPathRec(int toVertex) const
{
    std::ostringstream os;
    if (vTable_[toVertex].getPrevious() != NULL_VERTEX) {
        os << printPathRec(vTable_[toVertex].getPrevious());
        os << " to ";
    }
    os << vTable_[toVertex].getName();
    return os.str();
}

///////////////////////////////////////////////////////////////////////////
void Graph::clear() const
// initialize minimum path table    
{
    vector<Vertex>::const_iterator vi;
    for (vi = vTable_.begin(); vi != vTable_.end(); ++vi) {
        vi->setDistance(0);
        vi->setPrevious(NULL_VERTEX);
        vi->setExtra(0);
    }
}

///////////////////////////////////////////////////////////////////////////
int Graph::maximumConnectedSubgraphs()
// returns maximum amount of convex subgraphs
// observation: maybe different values are returned if graph is directed or not    
{
    int max = 0;
    vector<bool> vVisited(vTable_.size());

    // bfs
    vector<bool> vDiscovered(vTable_.size());   // initializes to false

    // TODO: what happens if vertex i doesn't exist?
    for (int i = 0; i < (int)vTable_.size(); ++i) {
        if (!vDiscovered[i]) {
            queue<int> q;
            q.push(i);
            vDiscovered[i] = true;
            max++;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                // traverse vertex v's adjacency list
                list<Edge>::const_iterator li;
                for (li = vTable_[v].getAdyList().begin(); 
                        li != vTable_[v].getAdyList().end(); ++li) {
                    int w = (*li).getDestiny();
                    if (!vDiscovered[w]) {
                        q.push(w);
                        vDiscovered[w] = true;
                    }
                }
            }
        } 
    }

    return max;
}

///////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, /*const*/ Graph& rhs) 
{
    os << (rhs.directed_ ? "Directed" : "Non Directed") << " Graph " << ": " << std::endl << std::endl;
    os << "Vertexes (" << rhs.nVertexes_ << "):" << std::endl << std::endl;
    for (int i = 0; i < rhs.nVertexes_; i++)
        os << rhs.vTable_[i].getName() << std::endl;
        
    os << std::endl;
    os << "Edges (" << rhs.nEdges_ << "):" << std::endl;
    os << "[Origin Vertex] -> [Destiny Vertex]: [Weight]" << std::endl << std::endl;

    for (int i = 0; i < rhs.nVertexes_; ++i) {
        Vertex& vert = rhs.vTable_[i];
        list<Edge>& ar = vert.getAdyList();

        list<Edge>::const_iterator li;
        for (li = ar.begin(); li != ar.end(); ++li)
            os << vert.getName() << "\t->\t" 
                << rhs.vTable_[(*li).getDestiny()].getName() 
                << ":\t" << (*li).getWeight() << std::endl;
    }
    return os;
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


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

    int ncases;
    cin >> ncases;
    for (int k = 1; k <= ncases && !cin.eof(); ++k) {
        // READ INPUT AND PROCESS
        Graph g;                // non-directed graph

        int npapers, nnames;
        cin >> npapers >> nnames;
        string line;
        getline(cin, line);     // ignore rest of line
        
        // for each paper, discover authors and add them to graph
        for (int i = 0; i < npapers; ++i) {
            // read paper
            getline(cin, line);
            vector<string> vAuthors;                // stores current paper's authors
            string::size_type to = line.find(':');  // authors appear before ':'
            line[to] = ',';                         // hack for easy name finding
            line = line.substr(0, to + 1);          // strip paper name
            to = 0;
            string::size_type from = 0;
            // last author may not contain initials
            while (to != line.length() - 1) {
                // get names
                to = line.find(',', to + 1);
                if (to != string::npos)
                    to = line.find(',', to + 1); // find 2nd comma
                if (to == string::npos)
                    to = line.length() - 1;
                string name = line.substr(from, to - from);
                from = to + 2;            // skip comma and whitespace (authors are separated by ', ')
                vAuthors.push_back(name);             
                g.addVertex(name);
            }
            // add edges between authors in vAuthors
            for (int i = 0; i < (int)vAuthors.size(); ++i)
                for (int j = i + 1; j < (int)vAuthors.size(); ++j)
                    g.addEdge(vAuthors[i], vAuthors[j]);
        }

        vector<string> vNames(nnames);  // stores the authors that must appear in output
        for (int i = 0; i < nnames; ++i) {
            getline(cin, line);
            vNames[i] = line;
            // add names from the list of names to graph
            // in case names without a paper appear
            g.addVertex(line);
        }

#ifdef DEBUG
        cout << START_DEBUG;
        cout << g;
        cout << END_DEBUG;
#endif

        // SHOW OUTPUT
        cout << "Scenario " << k << endl;
        // show authors in order of appearance
        for (int i = 0; i < nnames; ++i) {
            cout << vNames[i] << " ";
            long dist = g.shortestDistance(vNames[i], ERDOS);
            if (dist == g.INFINITY)
                cout << "infinity" << endl;
            else 
                cout << dist << endl;
        }
    }

    return 0;
}

/* @END_OF_SOURCE_CODE */

