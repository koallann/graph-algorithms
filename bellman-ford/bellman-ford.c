#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WEIGHT_INFINITY INT_MAX

typedef struct edge {
    int u;
    int v;
    int w;
} edge_t;

typedef struct graph {
    int V;
    int E;
    edge_t *edges;
} graph_t;

graph_t* create_graph(int V, int E) {
    graph_t *graph = (graph_t*) malloc(sizeof(graph_t));
    edge_t *edges = (edge_t*) malloc(sizeof(edge_t) * E);

    graph->V = V;
    graph->E = E;
    graph->edges = edges;

    return graph;
}

void initialize_distances(int n, int *distances) {
    for (int i=0; i<n; i++) {
        distances[i] = WEIGHT_INFINITY;
    }
}

int* bellman_ford(graph_t *graph, int src) {
    int V = graph->V;
    int E = graph->E;

    int *distances = (int*) malloc(sizeof(int) * V);
    initialize_distances(V, distances);

    distances[src] = 0;

    for (int i=0; i<V-1; i++) {
        for (int j=0; j<E; j++) {
            int u = graph->edges[j].u;
            int v = graph->edges[j].v;
            int w = graph->edges[j].w;

            if (distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
            }
        }
    }

    return distances;
}

int main(int argc, char const *argv[]) {
    int V, E;
    scanf("%d %d", &V, &E);

    graph_t *graph = create_graph(V, E);

    for (int i=0; i<E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        graph->edges[i].u = --u;
        graph->edges[i].v = --v;
        graph->edges[i].w = w;
    }

    int *result = bellman_ford(graph, 0);

    printf("Distances:");
    for (int i=0; i<V; i++) printf(" %d", result[i]);
    printf("\n");

    return 0;
}
