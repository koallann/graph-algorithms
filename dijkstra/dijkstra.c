#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../util/heap/heap.h"

#define WEIGHT_NOT_CONNECTED -1
#define WEIGHT_INFINITY INT_MAX

void initialize_graph(int n, int graph[n][n]) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            graph[i][j] = WEIGHT_NOT_CONNECTED;
        }
    }
}

void initialize_visited(int n, int visited[n]) {
    for (int i=0; i<n; i++) {
        visited[i] = 0;
    }
}

void initialize_distances(int n, int distances[n]) {
    for (int i=0; i<n; i++) {
        distances[i] = WEIGHT_INFINITY;
    }
}

int* dijkistra(int n, int graph[n][n], int src) {
    int visited[n];
    initialize_visited(n, visited);

    int* distances = (int*) malloc(sizeof(int)*n);
    initialize_distances(n, distances);

    heap_t *queue = heap_create(n);

    distances[src] = 0;
    heap_enqueue(queue, distance_create(src, 0));

    while (!heap_is_empty(queue)) {
        distance_t *d = heap_dequeue(queue);
        
        int u = d->to_vertex;
        int distance = d->value;

        if (visited[u]) continue;
        visited[u] = 1;

        for (int i=0; i<n; i++) {
            int w = graph[u][i];
            if (w == WEIGHT_NOT_CONNECTED) continue;

            if (distance + w < distances[i]) {
                distances[i] = distance + w;
                heap_enqueue(queue, distance_create(i, distances[i]));
            }
        }
    }

    return distances;
}

int main(int argc, char const *argv[])
{
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

    int *result = dijkistra(V, graph, 0);

    printf("Distances:");
    for (int i=0; i<V; i++) printf(" %d", result[i]);
    printf("\n");

    return 0;
}
