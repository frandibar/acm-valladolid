
/**************************************************************************
 GRAPH Library Header
 by: Francisco Dibar
 date: Aug-21-2006
TODO: finish dijkstra
**************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using std::list;
using std::map;
using std::pair;
using std::queue;
using std::string;
using std::vector;

///////////////////////////////////////////////////////////////////////////
class Edge 
{
public:
    // constructor
    Edge(int d, int w) : _destiny(d), _weight(w) {}
    
    // getters
    inline int getDestiny() const { return _destiny; }
    inline int getWeight()  const { return _weight; }
    
    // setters
    inline void setDestiny(int d) { _destiny = d; }
    inline void setWeight(int w) { _weight = w; }

private:
    int _destiny;
    int _weight;
};

///////////////////////////////////////////////////////////////////////////
class Vertex 
{
public:
    // constructor
    Vertex(const string& a_Name = "") : _name(a_Name) {}

    // getters
    inline string  getName()      const { return _name; }
    inline int     getDistance()  const { return _distance; }
    inline int     getPrevious()  const { return _previous; }
    inline int     getExtra()     const { return _extra; }
    inline int     getEdgeCount() const { return _adylist.size(); }
    inline list<Edge>& getAdyList() { return _adylist; }        // TODO: should be const

    // setters
    inline void setName(const string& a_Name) { _name = a_Name; }
    // the following sets are const since mutable variables are being modified
    inline void setDistance(int dist) const { _distance = dist; }
    inline void setPrevious(int prev) const { _previous = prev; }
    inline void setExtra(int extra) const { _extra = extra; }
    inline void setAdyList(list<Edge>& a_List) { _adylist = a_List; }

private:
    string _name;           // vertex real name
    list<Edge> _adylist;    // adjacency list, where edges are inserted
    mutable int _distance;  // weight (after performing algorithm)
    mutable int _previous;  // previous vertex in minimum path
    mutable int _extra;     // extra variable used in algorithms
};

// Type for pointer to function whose argument is a reference to Vertex
// Should be user defined, and will be applied when visiting vertex.
typedef void (*PROC_VISIT_VERT)(const Vertex&);

///////////////////////////////////////////////////////////////////////////
class Graph 
{
public:
    // constructor
    Graph(bool directed = false) : _directed(directed), _nVertexes(0), _nEdges(0) {}
    
    // getters
    int getEdgeCount() const { return _nEdges; }
    int getVertexCount() const { return _nVertexes; }

    // traversing
    void bfs(const string&); // const;
    long shortestDistance(const string&, const string&); // const;
    inline void dfs(const string&); // const;
    void minPathNoWeight(const string&); // const;
    string showPath(const string&) const;
    inline void setProcess(PROC_VISIT_VERT fn) { _procVisitVertex = fn; }

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
    int  addVertexToDictionary(const string&, bool*);
    void clear() const;
    bool dijkstra(int);
    void dfs(int);

    string printPathRec(int) const;

private:
    bool _directed;                     // directed or undirected graph
    map<string, int> _mapVertexes;      // links vertex number with name
    vector<Vertex> _vTable;             // stores vertexes
    int _nVertexes;                     // # of vertexes
    int _nEdges;                        // # of edges
    PROC_VISIT_VERT _procVisitVertex;   // pointer to function that applies on visited vertex
};

///////////////////////////////////////////////////////////////////////////

#endif  // GRAPH_H_INCLUDED


/**************************************************************************
 GRAPH Library Implementation
 by: Francisco Dibar
 date: Aug-21-2006
**************************************************************************/

///////////////////////////////////////////////////////////////////////////
void Graph::addEdge(const string& aOrigin, const string& aDestiny, int aWeight = 1)
{
    // add vertexes if they don't exist
    addVertex(aOrigin);
    addVertex(aDestiny);

    // get vertex indexes from hash table
    int orig = _mapVertexes[aOrigin];
    int dest = _mapVertexes[aDestiny];

    addInternalEdge(orig, dest, aWeight);
    if (!_directed) 
        // add edge going opposite direction
        addInternalEdge(dest, orig, aWeight);

}

///////////////////////////////////////////////////////////////////////////
bool Graph::addInternalEdge(int aOrigin, int aDestiny, int aWeight)
// add edge, if it exists then weight is modified, else return true    
{
    list<Edge>::iterator li;
    bool found = false;

    // find edge in list
    for (li = _vTable[aOrigin].getAdyList().begin(); 
                    !found && (li != _vTable[aOrigin].getAdyList().end()); ++li) {
        Edge &ed = *li;
        if (ed.getDestiny() == aDestiny) {
            ed.setWeight(aWeight);
            found = true;
        }
    }
    if (!found) {
        // add Edge
        (_vTable[aOrigin].getAdyList()).push_back(Edge(aDestiny, aWeight));
        _nEdges++;
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool Graph::addVertex(const string& aName)
// if vertex doesn't exist, adds it and returns true    
{
    bool notExists;
    addVertexToDictionary(aName, &notExists);
    if (notExists) {     
        _vTable.push_back(Vertex(aName));
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
int Graph::addVertexToDictionary(const string& aName, bool *notExists)
// if aName already exists, then return internal number, if not add to dictionary    
{
    // duplicate keys not allowed, if it already exists then it is not inserted
    typedef map<string, int>::iterator mi;
    pair<mi, bool> res; 
    // insert returns pair(iterador, bool) with bool = true if inserted and false if already existed
    res = _mapVertexes.insert(map<string, int>::value_type(aName, _nVertexes));
    if (res.second) {   // indicates if added or not
        _nVertexes++;
        *notExists = true;
    } else
        *notExists = false;
    
    return _mapVertexes[aName];
}

///////////////////////////////////////////////////////////////////////////
long Graph::shortestDistance(const string& aFromVertex, const string& aToVertex) //const
// returns shortest distance from aFromVertex to aToVertex    
// precondition: _procVisitVertex is valid    
{
    if (aFromVertex == aToVertex)
        return 0;

    // applies bfs
    int idFromVertex = _mapVertexes.find(aFromVertex)->second; // _mapVertexes[aFromVertex] isn't const
    int idToVertex = _mapVertexes.find(aToVertex)->second;

    // I use _vTable.size() instead of _nVertexes because if vertexes are eliminated
    // maybe idVertex > _nVertexes
    vector<bool> vProcessed(_vTable.size());  // stores visited and processed vertexes
    vector<bool> vDiscovered(_vTable.size()); // stores discovered but not processed vertexes
    vector<int> vParent(_vTable.size());

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
        for (li = _vTable[v].getAdyList().begin(); li != _vTable[v].getAdyList().end(); ++li) {
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
// precondition: _procVisitVertex is valid    
{
    //int idFromVertex = _mapVertexes[aFromVertex];
    int idFromVertex = _mapVertexes.find(aFromVertex)->second; // _mapVertexes[aFromVertex] isn't const

    // I use _vTable.size() instead of _nVertexes because if vertexes are eliminated
    // maybe idVertex > _nVertexes
    vector<bool> vProcessed(_vTable.size()); 
    vector<bool> vDiscovered(_vTable.size());
    vector<int> vParent(_vTable.size());

    queue<int> q;
    q.push(idFromVertex);
    vDiscovered[idFromVertex] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        _procVisitVertex(_vTable[v]);
        vProcessed[v] = true;
        // traverse vertex v's edge list
        list<Edge>::const_iterator li;
        for (li = _vTable[v].getAdyList().begin(); li != _vTable[v].getAdyList().end(); ++li) {
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

    int idOriginVertex = _mapVertexes[originVertex];
    clear();
    _vTable[idOriginVertex].setDistance(0);
    q.push(idOriginVertex);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        list<Edge>& getAdyList = _vTable[v].getAdyList();
        list<Edge>::iterator li;
        for (li = getAdyList.begin(); 
                li != getAdyList.end(); ++li) {
            Edge &ar = *li;
            int w = ar.getDestiny();
            if (_vTable[w].getDistance() == INFINITY) {
                _vTable[w].setDistance(_vTable[v].getDistance() + 1); 
                _vTable[w].setPrevious(v); 
                q.push(w);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
inline void Graph::dfs(const string& aFromVertex)
{
    int idFromVertex = _mapVertexes[aFromVertex];
    dfs(idFromVertex);
}

///////////////////////////////////////////////////////////////////////////
void Graph::dfs(int idFromVertex)
// precondition: _procVisitVertex is valid    
{
    // I use _vTable.size() instead of _nVertexes because if vertexes are eliminated
    // maybe idVertex > _nVertexes
    vector<bool> vProcessed(_vTable.size()); 
    vector<bool> vDiscovered(_vTable.size());
    vector<int> vParent(_vTable.size());

    vDiscovered[idFromVertex] = true;
    _procVisitVertex(_vTable[idFromVertex]);

    list<Edge>::const_iterator li;
    for (li = _vTable[idFromVertex].getAdyList().begin(); 
            li != _vTable[idFromVertex].getAdyList().end(); ++li) {
        int w = (*li).getDestiny();
        if (!vDiscovered[w]) {
            vParent[w] = idFromVertex;
            dfs(w);
        } else if (!vProcessed[w])
            _procVisitVertex(_vTable[w]);
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
    _vTable[originVertex].Distancia() = 0;
    //pq.push(priority_queue<Vertex, less<Vertex> >::value_type(originVertex, 0));
    pq.push(_vTable[originVertex]);
*/
/*
    int v, w;
    CColaPrioridad cp;
    CElementoCola vrec(NULL_VERTEX);
    CVertex *pVertex = (CVertex *)_vTable->ElementAt(nodoOrigen);

    LimpiarDatos();
    pVertex->Distancia() = 0;
    cp.Insertar(new CElementoCola(nodoOrigen, 0));

    for (int nodosVistos = 0; nodosVistos < _nVertexes; nodosVistos++) {
        do {
            if (cp.Vacia())
                return;
            vrec.Destino() = cp.EliminarMin();
            pVertex = (CVertex *)_vTable->ElementAt(vrec.Destino());
        } while (pVertex->Conocido() == false);
        
        v = vrec.Destino();
        pVertex = (CVertex *)_vTable->ElementAt(v);
        pVertex->Conocido() = true;

        CObList *pLista = new CObList;
        // copiar la lista de adyacencia para el Vertex v en pLista
        pLista->AddHead(pVertex->ObtenerLista());

        POSITION pos = pLista->GetHeadPosition();
        for ( ; pos != NULL ; pLista->GetNext(pos)) {
            w = ((CEdge *)pLista->GetAt(pos))->Destino();
            int cvw = ((CEdge *)pLista->GetAt(pos))->Costo();
            CVertex *pVertexW = (CVertex *)_vTable->ElementAt(w);
            
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
    mi = _mapVertexes.find(aName);
    return (mi != _mapVertexes.end());
}

///////////////////////////////////////////////////////////////////////////
string Graph::showPath(const string& aFromVertex) const
{
    std::ostringstream os;
    int idToVertex = _mapVertexes.find(aFromVertex)->second; // _mapVertexes[aFromVertex] isn't const
    if (_vTable[idToVertex].getDistance() == INFINITY)
        os << _vTable[idToVertex].getName() << " is unreachable" << std::endl;
    else {
        os << printPathRec(idToVertex);
        os << "The weight is " << _vTable[idToVertex].getDistance() << std::endl;
    }
    return os.str();
}

///////////////////////////////////////////////////////////////////////////
string Graph::printPathRec(int toVertex) const
{
    std::ostringstream os;
    if (_vTable[toVertex].getPrevious() != NULL_VERTEX) {
        os << printPathRec(_vTable[toVertex].getPrevious());
        os << " to ";
    }
    os << _vTable[toVertex].getName();
    return os.str();
}

///////////////////////////////////////////////////////////////////////////
void Graph::clear() const
// initialize minimum path table    
{
    vector<Vertex>::const_iterator vi;
    for (vi = _vTable.begin(); vi != _vTable.end(); ++vi) {
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
    vector<bool> vVisited(_vTable.size());

    // bfs
    vector<bool> vDiscovered(_vTable.size());   // initializes to false

    // TODO: what happens if vertex i doesn't exist?
    for (int i = 0; i < (int)_vTable.size(); ++i) {
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
                for (li = _vTable[v].getAdyList().begin(); 
                        li != _vTable[v].getAdyList().end(); ++li) {
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
    os << (rhs._directed ? "Directed" : "Non Directed") << " Graph " << ": " << std::endl << std::endl;
    os << "Vertexes (" << rhs._nVertexes << "):" << std::endl << std::endl;
    for (int i = 0; i < rhs._nVertexes; i++)
        os << rhs._vTable[i].getName() << std::endl;
        
    os << std::endl;
    os << "Edges (" << rhs._nEdges << "):" << std::endl;
    os << "[Origin Vertex] -> [Destiny Vertex]: [Weight]" << std::endl << std::endl;

    for (int i = 0; i < rhs._nVertexes; ++i) {
        Vertex& vert = rhs._vTable[i];
        list<Edge>& ar = vert.getAdyList();

        list<Edge>::const_iterator li;
        for (li = ar.begin(); li != ar.end(); ++li)
            os << vert.getName() << "\t->\t" 
                << rhs._vTable[(*li).getDestiny()].getName() 
                << ":\t" << (*li).getWeight() << std::endl;
    }
    return os;
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////////////////
void showVertexName(const Vertex& v)
{
    cout << v.getName() << endl;
}

///////////////////////////////////////////////////////////////////////////
int main()
{
    // test class
    Graph g;
    g.addEdge("v1", "v2");
    g.addEdge("v2", "v3");
    g.addEdge("v1", "v3");
    //cout << g;
    //g.setProcess(showVertexName);
    //g.bfs("v1");
    cout << g.shortestDistance("v1", "v3") << endl;
    cout << g.shortestDistance("v1", "XXX") << endl;
    return 0;
}

