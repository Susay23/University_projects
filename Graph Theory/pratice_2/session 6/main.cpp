#include <stdio.h>

typedef struct{
    int A[101][101];
    int n;
}Graph;

void init_graph(Graph *G, int n){
    G->n = n;
    for(int i = 0; i<=n;i++){
        for(int j = 0; j <= n; j++){
            G->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int u, int v){
    G->A[u][v] = 1;
    G->A[v][u] = 1;
}

void DFS(Graph *G, int start, int visited[], int parent){
    visited[start] = 1;
    if(parent == 0){
        printf("%d có đỉnh cha là %d => %d là gốc \n", start, parent, start);
    }else{
        printf("%d có đỉnh cha là %d\n", start, parent);
    }   
    for(int i = 1; i<=G->n;i++){
        if(G->A[start][i] == 1 && visited[i] == 0){
            DFS(G,i,visited,start);
        }
    }
}

int main(){
    freopen("dt.txt", "r", stdin);
    int n,m;
    scanf("%d%d", &n,&m);
    Graph G;
    init_graph(&G,n);
    int u,v;
    for(int i = 0; i < m;i++){
        scanf("%d%d", &u,&v);
        add_edge(&G,u,v);
    }

    int visited[101];
    int parent = 0;
    for(int i = 1; i<=n;i++){
        if(visited[i] == 0){
            DFS(&G,i,visited,parent);
        }
    }
}