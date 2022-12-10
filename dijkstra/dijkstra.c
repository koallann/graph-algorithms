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

int* dijkistra(int n, int graph[n][n], int source) {
    int visited[n];
    initialize_visited(n, visited);

    int* distances = (int*) malloc(sizeof(int)*n);
    initialize_distances(n, distances);

    heap_t *queue = heap_create(n);

    distances[source] = 0;
    heap_enqueue(queue, distance_create(source, 0));

    while (!heap_is_empty(queue)) {
        distance_t *d = heap_dequeue(queue);
        
        int vertex = d->to_vertex;
        int distance = d->value;

        if (visited[vertex]) continue;
        visited[vertex] = 1;

        for (int i=0; i<n; i++) {
            int weight = graph[vertex][i];
            if (weight == WEIGHT_NOT_CONNECTED) continue;

            int partial_distance = distance + weight;
            if (partial_distance < distances[i]) {
                distances[i] = partial_distance;
                heap_enqueue(queue, distance_create(i, partial_distance));
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
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);

        graph[--from][--to] = weight;
        graph[to][from] = weight;
    }

    int *result = dijkistra(V, graph, 0);

    printf("Distances:");
    for (int i=0; i<V; i++) printf(" %d", result[i]);
    printf("\n");

    return 0;
}
