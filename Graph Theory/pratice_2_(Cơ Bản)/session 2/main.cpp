
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int data[101];
    int current;
}stack;

void make_null(stack *s){
    s->current = -1;
}

void push(stack *s, int x){
    s->current++;
    s->data[s->current] = x;
}

int pop(stack *s){
    return s->data[s->current--];
}

int isempty(stack *s){
   return s->current == -1; 
}
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

void DPS(Graph G, int x, int visited[]){
    stack s;
    make_null(&s);
    push(&s, x);
    while(!isempty(&s)){
        int u = pop(&s);
        if(visited[u] == 1){
            continue;
        }
        visited[u] = 1;
        printf("%d\n",u);
        for(int v = 1; v<=G.n;v++){ 
            if(G.A[u][v]==1&&visited[v]==0){
                push(&s,v);
            }
        }
    }
}

int main(){
    Graph G;
    freopen("dt.txt","r",stdin);
   	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

    int visited[101] = {0};
    for(int i= 1; i<=n;i++){
        if(visited[i] == 0){
            DPS(G,i,visited);
        }
    }
}