#include <stdio.h>
#include <stdlib.h>

struct vertex {
	char val;
	int weight;
	struct vertex *next;
};

struct graph {
	int numVertex;
	struct vertex **adjList;
};

struct graph * createGraph(char arr[], int numVertex)
{
	struct graph *g = malloc(sizeof(struct graph));
	int i;

	g->numVertex = numVertex;
	g->adjList = malloc(sizeof(struct vertex*)*numVertex);
	for (i = 0; i < numVertex; i++) {
		g->adjList[i] = malloc(sizeof(struct vertex));
		g->adjList[i]->val = arr[i];
		g->adjList[i]->next = g->adjList[i];
		g->adjList[i]->weight = 0;
	}

	return g;
}

struct vertex* findVertex(struct graph *g, char val)
{
	int i;
	for (i = 0; i < g->numVertex; i++) {
		if (g->adjList[i]->val == val)
			break;
	}

	if (i == g->numVertex) {
		printf("Vertex not found.. Error\n");
		return NULL;
	}

	return g->adjList[i];

}

void addEdge(struct graph *g, char src, char dst, int weight)
{
	struct vertex *v = findVertex(g, src);
	struct vertex *temp  = malloc(sizeof(struct vertex));
	temp->val = dst;
	temp->weight = weight;
	if ( v->next == v) {
		v->next = temp;
		temp->next = v;
	} else {
		struct vertex *t = v->next;
		v->next = temp;
		temp->next = t;
	}

	v = findVertex(g, dst);
	temp  = malloc(sizeof(struct vertex));
	temp->weight = weight;
	temp->val = src;

	if ( v->next == v) {
		v->next = temp;
		temp->next = v;
	} else {
		struct vertex *t = v->next;
		v->next = temp;
		temp->next = t;
	}
}

int appendVertex(struct graph *g, char val)
{
	int numVertex = ++g->numVertex;
	printf(" realloc for %d vertex\n", numVertex);
	g->adjList = realloc(g->adjList, sizeof(struct vertex *)* numVertex);

	numVertex--;
	g->adjList[numVertex] = malloc(sizeof(struct vertex));
	g->adjList[numVertex]->val = val;
	g->adjList[numVertex]->next = g->adjList[numVertex];
}

void printGraph(struct graph *g)
{
	int i;

	for ( i = 0; i < g->numVertex; i++) {
		struct vertex *start = g->adjList[i];
		struct vertex *temp = start->next;
		printf("Vertex = %c -> ", g->adjList[i]->val);

		while(temp != start) {
			printf(" %c ", temp->val);
			temp = temp->next;
		};
		printf("\n");
	}
}

int main(void)
{
	char arr[] = { 'A', 'B', 'C', 'D'};
	struct graph *g = createGraph(arr, 4);

	addEdge(g, 'A', 'B', 1);
	addEdge(g, 'B', 'C', 1);

	appendVertex(g, 'Z');
	addEdge(g, 'Z', 'B', 1);
	addEdge(g, 'Z', 'C', 1);
	printGraph(g);

}
