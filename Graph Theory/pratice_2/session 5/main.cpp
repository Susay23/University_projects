#include<stdio.h>

typedef struct 
{
    int A[101][101];
    int n;
}Graph;

typedef struct 
{
    int data[101];
    int current;
}Stack;

int isempty(Stack *s){
    return s->current == -1;
}

void makenull(Stack *s){
    s->current = -1;
}

void push(Stack *s, int x){
    s->current++;
    s->data[s->current] = x;
}

int pop(Stack *s){
    return s->data[s->current--];
}


void init_graph(Graph *G, int n){
    G->n = n;
    for(int i = 0; i<=n; i++){
        for(int j = 0; j <= n;j++){
            G->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int u, int v){
    G->A[u][v] = 1;
    G->A[v][u] = 1;
}

void DFS(Graph G, int start, int visited[],int parent[],int parentNode){
    visited[start] = 1;
    parent[start] = 0;
    for(int i = 1; i<=G.n;i++){
        if(G.A[start][i] == 1 && visited[i] == 0){
            DFS(G,i,visited,parent,start);
        }
    }
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

    int visited[105] = {0};
    int parent[105];
    int parentNode = 0;
    for(int i = 1; i<=n;i++){
        if(visited[i] == 0){
            DFS(G,i,visited,parent,parentNode);
        }
    }
    for(int i = 1; i <= n; i++){
        if(parent[i] == 0){
            printf("%d %d có cha là %d\n", i, parent[i]);
        }else{
            printf("%d %d\n", i, parent[i]);
        }
    }
}