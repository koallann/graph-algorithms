#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "./heap/heap.h"

#define WEIGHT_NOT_CONNECTED -1
#define WEIGHT_INFINITY INT_MAX

void initialize_graph(int V, int graph[V][V]) {
    for (int i=0; i<V; i++) {
        for (int j=0; j<V; j++) {
            graph[i][j] = WEIGHT_NOT_CONNECTED;
        }
    }
}

void initialize_visited(int V, int visited[V]) {
    for (int i=0; i<V; i++) {
        visited[i] = 0;
    }
}

void initialize_distances(int V, int distances[V]) {
    for (int i=0; i<V; i++) {
        distances[i] = WEIGHT_INFINITY;
    }
}

int* dijkistra(int V, int graph[V][V], int src) {
    int visited[V];
    initialize_visited(V, visited);

    int* distances = (int*) malloc(sizeof(int)*V);
    initialize_distances(V, distances);

    heap_t *queue = heap_create(V);

    distances[src] = 0;
    heap_enqueue(queue, distance_create(src, 0));

    while (!heap_is_empty(queue)) {
        distance_t *d = heap_dequeue(queue);
        
        int u = d->to_vertex;
        int distance = d->value;

        if (visited[u]) continue;
        visited[u] = 1;

        for (int i=0; i<V; i++) {
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
