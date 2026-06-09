#include <stdio.h>

#define MAX_EDGES 1000

typedef struct  {
	 int x, y;
} Edge;
typedef struct {
	int n, m;
	Edge edges[MAX_EDGES];
} Graph;

void init_graph(Graph* G, int n){
	G->n = n;
	G->m = 0;
}

void add_edge(Graph* G, int x, int y){
    if(G->m < MAX_EDGES){
        if(x <= G->n && y <= G->n){
            G->edges[G->m].x = x;
            G->edges[G->m].y = y;
            G->m++;
        }
    }
}

int main(){
    Graph G;
    init_graph(&G, 5);
    add_edge(&G, 1, 2);
    add_edge(&G, 1, 3);
    add_edge(&G, 2, 4);
    add_edge(&G, 3, 4);
    add_edge(&G, 4, 5);

    printf("Number of vertices: %d\n", G.n);
    printf("Number of edges: %d\n", G.m);
    for(int i=0; i<G.m; i++){
        printf("Edge %d: (%d, %d)\n", i+1, G.edges[i].x, G.edges[i].y);
    }

    return 0;
}