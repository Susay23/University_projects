#include<stdio.h>

typedef struct{
    int a[100][100];
    int n;
} Graph;

void init_graph(Graph *G, int n){
    G->n = n;
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0; j < n; j++){
            G->a[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int u, int v){
    G->a[u][v] = 1;
    G->a[v][u] = 1;
}

void DFS(Graph *G, int start, int visited[]){
    visited[start] = 1;
    for(int i = 0; i < G->n;i++){
        if(G->a[start][i] == 1 && visited[i] == 0){
            DFS(G,i,visited);
        }
    }
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

    int visited[101] = {0};

}