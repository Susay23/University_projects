#include<stdio.h>
#include<iostream>

using namespace std;


typedef struct
{
    int n, m;
    int Edges[100][100];
} Graph;

void init_graph(Graph* G, int n) {
    G->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G->Edges[i][j] = 0;
}

void add_edge(Graph* G, int u, int v) {
    G->Edges[u][v] = 1;
    G->Edges[v][u] = 1;
}

int deg(Graph* G, int x) {
    int count = 0;
    for (int v = 1; v <= G->n; v++)
        count += G->Edges[x][v];
    return count;
}

int maxDegD(Graph* G){
    int maxD = 0;
    int maxV = 1;
    for(int x = 1;x<G->n;x++){
        int d = deg(G,x);
        if(d>maxD){
            maxD=d;
            maxV=x;
        }
    }
    return maxD;
}


int maxDegV(Graph* G){
    int maxD = 0;
    int maxV = 1;
    for(int x = 1;x<G->n;x++){
        int d = deg(G,x);
        if(d>maxD){
            maxD=d;
            maxV=x;
        }
    }
    return maxV;
}

int main(){
    freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
    int maxV = maxDegD(&G);
    int maxD = maxDegV(&G);

    printf("max D: %d\n", maxD);
    printf("max V: %d\n", maxV);

    return 0;
}