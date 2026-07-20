#include<stdio.h>
#include<iostream>

using namespace std;

typedef struct {
    int A[100][100];
    int n;
} Graph;

void init_graph(Graph* G, int n) {
    G->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph* G, int u, int v) {
    G->A[u][v] = 1;
    G->A[v][u] = 1;
}

typedef struct{
    int data[100];
    int front, rear;
}Queue;
void make_null_Q(Queue* Q){
    Q->front=0;
    Q->rear=-1;
}
void enqueue(Queue* Q, int x){
    Q->rear++;
    Q->data[Q->rear]=x;
}
int front(Queue* Q){
    return Q->data[Q->front];
}
void dequeue(Queue* Q){
    Q->front++;
}
int empty_Q(Queue* Q){
    return Q->front > Q->rear;
}
void print_Q(Queue* Q){
    int i;
    for (i=1; i<=Q->rear; i++){
        printf("%d ", front(Q));
        dequeue(Q);
    }
}

// BFS_Full(G, n):
//     visited[1..n] = FALSE
    
//     for start = 1 to n:
//         if visited[start] == FALSE:
//             // Bắt đầu một lần BFS mới từ đỉnh chưa thăm
            
//             make_null_Q(Q)
//             enqueue(Q, start)
//             visited[start] = TRUE
            
//             while Q không rỗng:
//                 u = front(Q)
//                 dequeue(Q)
//                 print(u) u đại diện cho đỉnh (node/vertex) hiện tại đang được xử lý trong quá trình duyệt đồ thị.
                
//                 for mỗi đỉnh v kề với u (theo thứ tự tăng dần):
//                     if visited[v] == FALSE:
//                         visited[v] = TRUE
//                         enqueue(Q, v)

void BFS(Graph G, int n){
    int visited[G.n+1];
    for(int i = 1; i < G.n + 1; i++){
        visited[i] = 0;
    }

    Queue q;

    for(int start = 1; start <= G.n; start ++){
        if(visited[start] == 0){
            make_null_Q(&q);
            enqueue(&q,start);
            visited[start] = 1;
        }

        while(!empty_Q(&q)){
            int u = front(&q);
            dequeue(&q);
            printf("dinh cua do thi: %d \n", u);
            for(int v = 1; v <= G.n; v++){
                if(visited[v] == 0 && G.A[u][v] == 1){
                    visited[v] = 1;
                    enqueue(&q,v);
                }
            }
        }
        
    }
}

int main(){
    freopen("dt.txt", "r", stdin);
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

     BFS(G,n);
}