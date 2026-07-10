#include<stdio.h>

typedef struct 
{
    int A[101][101];
    int n;
}Graph;

void init_graph(Graph *G, int n){
    G->n = n;
    for(int i = 0; i<=G->n; i++){
        for(int j = 0; j <= G->n;j++){
            G->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int u, int v){
    G->A[u][v] = 1;
    G->A[v][u] = 1;
}


int main(){
    freopen("dt.txt","r", stdin);
    int n,m;
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G,n);

    int u,v;
    for(int i = 0; i<m;i++){
        scanf("%d%d", &u,&v);
        add_edge(&G,u,v);
    }

    
}