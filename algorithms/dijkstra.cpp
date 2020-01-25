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
    adjList[src].push_back(make_pair(dest, weight));
}

void dkstrGraph::dijkstra(int start, int dest){
    priority_queue<iPair, vector<iPair> , greater<iPair>> pq;

    int distances[Vnum];
    for(int i = 0; i < Vnum; i++) distances[i] = INT_MAX;
    distances[start] = 0;
    pq.push(make_pair(0, start));
    int ansDist = distances[dest];

    while (!pq.empty()) {
        int src = pq.top().second;
        pq.pop();

        list<iPair>::iterator it;
        for (it = adjList[src].begin(); it != adjList[src].end(); it++) {
            int dist = (*it).first;
            int v = (*it).second;
            int newDist = distances[src] + dist;
            if (newDist < ansDist && newDist < distances[v]) {
                distances[v] = newDist;
                if (v == dest) ansDist = newDist;
                pq.push(make_pair(distances[v], v));
            }
        }
    }
    cout << "The shortest distance is " << ansDist;
}