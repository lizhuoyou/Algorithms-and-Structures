#include <iostream>
#include <list>

using namespace std;

class DFS_graph{
private:
    int Vamount;
    list<int> *adjList;
    void DFSplus(int v, bool visited[]);        // used by DFS
public:
    DFS_graph(int numOfVertices);

    ~DFS_graph();

    void addEdge(int vertice, int adjV);

    void DFS(int startV);
};

DFS_graph::DFS_graph(int numOfVertices){
    Vamount = numOfVertices;
    adjList = new list<int>[numOfVertices];
}

DFS_graph::~DFS_graph() {
    delete [] adjList;
}

void DFS_graph::addEdge(int vertice, int adjV) {
    adjList[vertice].push_back(adjV);
}

void DFS_graph::DFSplus(int vertice, bool *visited) {
    visited[vertice] = true;
    cout << vertice << " ";
    list<int>::iterator i;
    for (i = adjList[vertice].begin(); i != adjList[vertice].end(); i++) {
        if(!visited[*i]) DFSplus(*i, visited);
    }
}

void DFS_graph::DFS(int startV) {
    bool *visited = new bool[Vamount];
    for (int i = 0; i < Vamount; i++) visited[i] = false;
    DFSplus(startV, visited);
    delete [] visited;
}

int main(){
    DFS_graph dfsG = DFS_graph(4);
    dfsG.addEdge(0, 1);
    dfsG.addEdge(0, 2);
    dfsG.addEdge(1, 2);
    dfsG.addEdge(2, 0);
    dfsG.addEdge(2, 3);
    dfsG.addEdge(3, 3);

    cout << "DFS search from 2:" << endl;
    dfsG.DFS(2);
    cout << endl;
    return 0;
}