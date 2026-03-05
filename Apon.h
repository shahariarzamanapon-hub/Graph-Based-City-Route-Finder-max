#ifndef APON_H_INCLUDED
#define APON_H_INCLUDED

#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX 60
#define LEN 30


int V;
int graph[MAX][MAX];
char city[MAX][LEN];

int getIndex(char name[]) {
    for (int i = 0; i < V; i++) {
        if (strcmp(city[i], name) == 0)
            return i;
    }
    return -1;
}

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX,idx;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            idx = i;
        }
    }
    return idx;
}

void printPath(FILE *out, int parent[], int j) {
    if (parent[j] == -1) return;
    printPath(out, parent, parent[j]);
    fprintf(out, " -> %s", city[j]);
}

void dijkstra(int src, int dest) {
    int dist[MAX], visited[MAX], parent[MAX];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int c = 0; c < V - 1; c++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {

                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    FILE *out = fopen("output.txt", "w");

    fprintf(out, "Shortest Distance: %d\n", dist[dest]);
    fprintf(out, "Path: %s", city[src]);
    printPath(out, parent, dest);

    fclose(out);
}


#endif
