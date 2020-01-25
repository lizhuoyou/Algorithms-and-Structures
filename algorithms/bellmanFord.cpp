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

void graphDestructor(struct Graph *graph){
    delete graph->edges;
    delete [] graph;
}

void bellmanFord(struct graph *g, int src){
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
};

