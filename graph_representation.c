
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

Node *adj[MAX_VERTICES];

void addEdge(int u, int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    /* For an undirected graph, add the reverse connection too. */
    newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->vertex = u;
    newNode->next = adj[v];
    adj[v] = newNode;
}

void displayGraph(int vertices) {
    int i;
    for (i = 0; i < vertices; i++) {
        Node *temp = adj[i];
        printf("%d -> ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freeGraph(int vertices) {
    int i;
    for (i = 0; i < vertices; i++) {
        Node *temp = adj[i];
        while (temp != NULL) {
            Node *toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        adj[i] = NULL;
    }
}

int main(void) {
    int vertices, edges, i, u, v;

    printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &vertices) != 1 || vertices < 1 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter number of edges: ");
    if (scanf("%d", &edges) != 1 || edges < 0) {
        printf("Invalid number of edges.\n");
        return 1;
    }

    for (i = 0; i < edges; i++) {
        printf("Enter edge %d (u v): ", i + 1);
        if (scanf("%d %d", &u, &v) != 2 ||
            u < 0 || u >= vertices || v < 0 || v >= vertices) {
            printf("Invalid edge. Vertices must be between 0 and %d.\n", vertices - 1);
            freeGraph(vertices);
            return 1;
        }
        addEdge(u, v);
    }

    printf("\nAdjacency List:\n");
    displayGraph(vertices);
    freeGraph(vertices);
    return 0;
}
