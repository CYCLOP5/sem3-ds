#include <stdio.h>
#include <stdlib.h>

#define MAX 7

struct Node {
    int dest;
    struct Node* next;
};

struct AdjList {
    struct Node *head;
};

struct Graph {
    int numVertices;
    struct AdjList* array;
};

struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->array = (struct AdjList*)malloc(vertices * sizeof(struct AdjList));

    for (int i = 0; i < vertices; i++)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void printGraph(struct Graph* graph, char* cityNames[]) {
    printf("Adjacency List:\n");
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->array[v].head;
        printf("%s:", cityNames[v]);  
        while (temp) {
            printf(" ---> %s", cityNames[temp->dest]);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}

int time = 0;
int start[MAX];
int finish[MAX];
int visited[MAX];
int traversalOrder[MAX];
int orderIndex = 0;

void DFS(struct Graph* graph, int vertex, char* cityNames[]) {
    visited[vertex] = 1;
    start[vertex] = ++time;
    traversalOrder[orderIndex++] = vertex; 
    printf("reached %s (started at: %d)\n", cityNames[vertex], start[vertex]);

    struct Node* adjList = graph->array[vertex].head;
    struct Node* temp = adjList;

    while (temp != NULL) {
        int connectedVertex = temp->dest;

        if (!visited[connectedVertex])
            DFS(graph, connectedVertex, cityNames);

        temp = temp->next;
    }
    finish[vertex] = ++time;
    printf("done with %s (finished at: %d)\n", cityNames[vertex], finish[vertex]);
}

void doDFS(struct Graph* graph, int startVertex, char* cityNames[]) {

    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
        start[i] = 0;
        finish[i] = 0;
    }
    orderIndex = 0; 

    printf("DFS:\n");
    DFS(graph, startVertex, cityNames);

    printf("\nFinal DFS: ");
    for (int i = 0; i < orderIndex; i++) {
        printf("%s ", cityNames[traversalOrder[i]]);
    }
    printf("\n");

    printf("\n%-15s %-6s %-6s\n", "Vertex", "Start", "Finish");
    for (int i = 0; i < MAX; i++) {
        printf("%-15s %-6d %-6d\n", cityNames[i], start[i], finish[i]);
    }
}

int main() {
    struct Graph* graph = createGraph(MAX);

    addEdge(graph, 0, 1); 
    addEdge(graph, 0, 2); 
    addEdge(graph, 0, 5); 
    addEdge(graph, 2, 5);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 3);
    addEdge(graph, 4, 6);
    addEdge(graph, 3, 6);
    addEdge(graph, 3, 5);  

    char* cityNames[MAX] = {
        "EVERETT", 
        "SEATTLE", 
        "NORTH-BEND", 
        "CENTRALIA", 
        "OLYMPIA", 
        "SPOKANE", 
        "PORTLAND"
    };

    printGraph(graph, cityNames); 
    doDFS(graph, 0, cityNames); 

    return 0;
}
