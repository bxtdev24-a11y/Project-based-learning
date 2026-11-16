
#include <stdio.h>

#define MAX 20
#define INF 1000000000

int main(void) {
    int graph[MAX][MAX];
    int distance[MAX], visited[MAX] = {0};
    int n, source, i, j, count, u, minDistance;

    printf("Enter number of vertices (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
        return 1;

    printf("Enter adjacency matrix (0 means no edge; weights must be non-negative):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                printf("Invalid input. Use non-negative weights.\n");
                return 1;
            }
            if (i != j && graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    if (scanf("%d", &source) != 1 || source < 0 || source >= n)
        return 1;

    for (i = 0; i < n; i++)
        distance[i] = INF;
    distance[source] = 0;

    for (count = 0; count < n - 1; count++) {
        minDistance = INF;
        u = -1;

        for (i = 0; i < n; i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF &&
                distance[u] != INF &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest distances from vertex %d:\n", source);
    for (i = 0; i < n; i++) {
        if (distance[i] == INF)
            printf("To %d: Unreachable\n", i);
        else
            printf("To %d: %d\n", i, distance[i]);
    }

    return 0;
}
