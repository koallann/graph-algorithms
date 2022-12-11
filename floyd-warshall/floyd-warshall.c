#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITY INT_MAX

void initialize_graph(int V, int graph[V][V]) {
    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            graph[i][j] = i == j ? 0 : INFINITY;
        }
    }
}

void floyd_warshall(int V, int graph[V][V]) {
    for (int k=0; k<V; k++) {
        for (int i=0; i<V; i++) {
            for (int j=0; j<V; j++) {
                if (graph[i][k] == INFINITY
                    || graph[k][j] == INFINITY) continue;

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
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);

        graph[--from][--to] = weight;
        graph[to][from] = weight;
    }

    floyd_warshall(V, graph);

    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            if (graph[i][j] == INFINITY) printf(" I");
            else printf(" %d", graph[i][j]);
        }
        printf("\n");
    }

    return 0;
}
