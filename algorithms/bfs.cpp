#include <iostream>
#include <list>

using namespace std;

class BFS_graph{
private:
    int Vamount;
    list<int> *adjList;
public:
    BFS_graph(int numOfVertices);

    ~BFS_graph();

    void addEdge(int vertice, int adjV);

    void BFS(int startV);
};

BFS_graph::BFS_graph(int numOfVertices){
    Vamount = numOfVertices;
    adjList = new list<int>[numOfVertices];
}

BFS_graph::~BFS_graph() {
    delete [] adjList;
}

void BFS_graph::addEdge(int vertice, int adjV) {
    adjList[vertice].push_back(adjV);
}

void BFS_graph::BFS(int startV) {
    bool *visited = new bool[Vamount];
    for(int i= 0; i<Vamount;i++) visited[i] = false;
    list<int> queue;

    visited[startV] = true;
    queue.push_back(startV);

    while (!queue.empty()) {
        startV = queue.front();
        cout << startV << " ";
        queue.pop_front();

        list<int>::iterator i;
        for (i = adjList[startV].begin(); i != adjList[startV].end(); i++) {
            if(!visited[*i]){
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

int main(){
    BFS_graph bfsG = BFS_graph(4);
    bfsG.addEdge(0, 1);
    bfsG.addEdge(0, 2);
    bfsG.addEdge(1, 2);
    bfsG.addEdge(2, 0);
    bfsG.addEdge(2, 3);
    bfsG.addEdge(3, 3);

    cout << "BFS search from 1:" << endl;
    bfsG.BFS(1);
    cout << endl;
    return 0;
}