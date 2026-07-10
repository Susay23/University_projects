#include<stdio.h>

typedef struct{
    int A[101][101];
    int n;
}Graph;

void init_graph(Graph *g, int n){
    g->n = n;
    for(int i = 0; i<=n;i++){
        for(int j = 0; j<=n;j++){
            g->A[i][j]=0;
        }
    }
}

void add_edge(Graph *g, int u, int v){
    g->A[u][v] = 1;
    g->A[v][u] = 1;
}


int main(){
    freopen("dt.txt","r",stdin);
    int n,m;
    scanf("%d%d ", &n, &m);
    Graph G;
    init_graph(&G,n);
    int u,v;
    for(int i = 0; i<m;i++){
        scanf("%d%d ", &u,&v);
        add_edge(&G, u, v);
    }
}