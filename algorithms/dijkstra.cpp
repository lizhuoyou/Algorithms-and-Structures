#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <queue>

using namespace std;

typedef pair<int, int> iPair;

class dkstrGraph{
private:
    int Vnum;
    list<iPair> *adjList;
public:
    dkstrGraph(int V_amount);

    ~dkstrGraph();

    void addEdge(int src, int dest, int weight);

    void dijkstra(int start, int dest);
};

dkstrGraph::dkstrGraph(int V_amount) {
    Vnum = V_amount;
    adjList = new list<iPair>[V_amount];
}

dkstrGraph::~dkstrGraph() {
    delete [] adjList;
}

void dkstrGraph::addEdge(int src, int dest, int weight) {
    adjList[src].emplace_back(dest, weight);
    // the edge is single direction now; uncomment the following for double direction edge
    // adjList[dest].emplace_back(src, weight);
}

void dkstrGraph::dijkstra(int start, int dest){
    priority_queue<iPair, vector<iPair> , greater<iPair>> pq;

    int distances[Vnum];
    for(int i = 0; i < Vnum; i++) distances[i] = INT_MAX;
    distances[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int src = pq.top().second;
        if(src == dest) break;      // end when we find distance the destiny(when the distance is the shortest)
        pq.pop();

        list<iPair>::iterator it;
        for (it = adjList[src].begin(); it != adjList[src].end(); it++) {
            int v = (*it).first;
            int weight = (*it).second;
            int newDist = distances[src] + weight;
            if (newDist < distances[v]) {
                distances[v] = newDist;
                pq.push(make_pair(newDist, v));
            }
        }
    }

    cout << "The shortest distance from " << start << " to " << dest << " is " << distances[dest];
}

int main(){
    dkstrGraph g(9);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.dijkstra(0,8);

    return 0;
}