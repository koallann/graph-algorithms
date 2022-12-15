#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WEIGHT_INFINITY INT_MAX

void initialize_graph(int V, int graph[V][V]) {
    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            graph[i][j] = i == j ? 0 : WEIGHT_INFINITY;
        }
    }
}

void floyd_warshall(int V, int graph[V][V]) {
    for (int k=0; k<V; k++) {
        for (int i=0; i<V; i++) {
            for (int j=0; j<V; j++) {
                if (graph[i][k] == WEIGHT_INFINITY
                    || graph[k][j] == WEIGHT_INFINITY) continue;

                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    int V, E;
    scanf("%d %d", &V, &E);

    int graph[V][V];
    initialize_graph(V, graph);

    for (int i=0; i<E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        graph[--u][--v] = w;
        graph[v][u] = w;
    }

    floyd_warshall(V, graph);

    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            if (graph[i][j] == WEIGHT_INFINITY) printf(" I");
            else printf(" %d", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}
