#include <iostream>
#include <climits>

using namespace std;

struct edge{
    int src, dest, weight;
};

struct graph{
    int Vnum, Enum;
    struct edge *edges;
};

struct graph* graphGenerator(int V_amount, int E_amount){
    struct graph *g = new graph;
    g->Vnum = V_amount;
    g->Enum = E_amount;
    g->edges = new edge[E_amount];
    return g;
}

void graphDestructor(struct graph *g){
    delete [] g->edges;
    delete g;
}

void bellmanFord(struct graph *g, int src, int dest){
    int Vnum = g->Vnum;
    int Enum = g->Enum;

    int distances[Vnum];
    for(int i = 0; i < Vnum; i++) distances[i] = INT_MAX;
    distances[src] = 0;

    for (int i = 1; i < Vnum; i++) {
        for (int j = 0; j < Enum; j++) {
            int s = g->edges[j].src;
            int d = g->edges[j].dest;
            int w = g->edges[j].weight;
            if (distances[s] != INT_MAX && distances[s] + w < distances[d]) {
                distances[d] = distances[s] + w;
            }
        }
    }

    // check negative weight cycle.
    for (int i = 0; i < Enum; i++) {
        int s = g->edges[i].src;
        int d = g->edges[i].dest;
        int w = g->edges[i].weight;
        if (distances[s] != INT_MAX && distances[s] + w < distances[d]) {   // it has to be equal if no nag cycle.
            cerr << "\nError, negative weight cycle exits.\n";
            exit(1);
        }
    }

    cout << "The shortest distance from " << src << " to " << dest << " is " << distances[dest];
};

int main(){
    struct graph *g = graphGenerator(5, 8);

    // add edge 0-1 (or A-B in above figure)
    g->edges[0].src = 0;
    g->edges[0].dest = 1;
    g->edges[0].weight = -1;

    // add edge 0-2 (or A-C in above figure)
    g->edges[1].src = 0;
    g->edges[1].dest = 2;
    g->edges[1].weight = 4;

    // add edge 1-2 (or B-C in above figure)
    g->edges[2].src = 1;
    g->edges[2].dest = 2;
    g->edges[2].weight = 3;

    // add edge 1-3 (or B-D in above figure)
    g->edges[3].src = 1;
    g->edges[3].dest = 3;
    g->edges[3].weight = 2;

    // add edge 1-4 (or A-E in above figure)
    g->edges[4].src = 1;
    g->edges[4].dest = 4;
    g->edges[4].weight = 2;

    // add edge 3-2 (or D-C in above figure)
    g->edges[5].src = 3;
    g->edges[5].dest = 2;
    g->edges[5].weight = 5;

    // add edge 3-1 (or D-B in above figure)
    g->edges[6].src = 3;
    g->edges[6].dest = 1;
    g->edges[6].weight = 1;

    // add edge 4-3 (or E-D in above figure)
    g->edges[7].src = 4;
    g->edges[7].dest = 3;
    g->edges[7].weight = -3;

    bellmanFord(g, 0, 3);

    graphDestructor(g);
    return 0;
}