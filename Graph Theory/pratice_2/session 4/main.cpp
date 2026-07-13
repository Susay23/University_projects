#include<stdio.h>

typedef struct{
    int A[101][101];
    int n;
}Graph;

typedef struct{
    int data[1000];
    int front;
    int rear;
}Queue;

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


void initQueue(Queue *Q){
    Q->front = 0;
    Q->rear = 0;
}

int isEmpty(Queue *Q){
    if(Q->front == Q->rear){
        return 1;
    }
    return 0;
}

void enqueue(Queue *Q, int x){
    Q->data[Q->rear] = x;
    Q->rear = Q->rear + 1;
}

int dequeue(Queue *Q){
    int x = Q->data[Q->front];
    Q->front = Q->front + 1;
    return x;
}

void BFS(Graph *G, int start, int visited[], int parent[]){
    Queue q;
    initQueue(&q);
    visited[start] = 1;
    parent[start] = 0;
    enqueue(&q,start);

    while(!isEmpty(&q)){
        int u = dequeue(&q);

        for(int i = 1; i <= G->n; i++){
            if(G->A[u][i] == 1 && visited[i] == 0){
                visited[i] = 1;
                parent[i] = u;
                enqueue(&q,i);
            }
        }
    }
}


int main(){
    freopen("dt.txt","r",stdin);
    int n,m;
    scanf("%d%d ", &n, &m);
    Graph G;
    G.n = n;
    init_graph(&G,n);
    int u,v;
    for(int i = 0; i<m;i++){
        scanf("%d%d ", &u,&v);
        add_edge(&G, u, v);
    }
    int visited[101] = {0};
    int parent[105] = {0};
    for(int i = 1; i <= n; i ++){
        if(visited[i] == 0){
            BFS(&G,i,visited, parent);
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