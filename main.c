#include <stdio.h>
#include "Apon.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 60
#define LEN 30
int main()
{
    FILE *in = fopen("input.txt", "r");

    if (!in) {
        printf("input.txt not found\n");
        return 0;
    }

    fscanf(in, "%d", &V);

    for (int i = 0; i < V; i++)
        fscanf(in, "%s", city[i]);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    char a[LEN], b[LEN];
    int w;

    while (fscanf(in, "%s %s %d", a, b, &w) == 3) {
        int u = getIndex(a);
        int v = getIndex(b);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    fclose(in);

    char srcName[LEN], destName[LEN];

    printf("Enter source city: ");
    scanf("%s", srcName);

    printf("Enter destination city: ");
    scanf("%s", destName);

    int src = getIndex(srcName);
    int dest = getIndex(destName);

    if (src == -1 || dest == -1) {
        printf("City not found!\n");
        return 0;
    }

    dijkstra(src, dest);

    printf("Done! Check output.txt\n");

    return 0;
}
