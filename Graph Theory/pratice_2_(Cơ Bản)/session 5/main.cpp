#include <stdio.h>

typedef struct {
    int A[101][101];
    int n;
} Graph;

typedef struct {
    int u;
    int parent;
} Element;

typedef struct {
    Element data[101];
    int current;
} Stack;

void makenull(Stack *s) { s->current = -1; }
int isempty(Stack *s) { return s->current == -1; }
void push(Stack *s, Element x) { s->data[++(s->current)] = x; }
Element pop(Stack *s) { return s->data[(s->current)--]; }

void init_graph(Graph *G, int n) {
    G->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int u, int v) {
    G->A[u][v] = 1;
    G->A[v][u] = 1;
}

void DFS(Graph *G, int start, int visited[], int parent[]) {
    Stack s;
    makenull(&s);
    
    // Đẩy gốc vào stack với cha là 0
    Element e = {start, 0};
    push(&s, e);
    
    while (!isempty(&s)) {
        Element curr = pop(&s);
        int u = curr.u;
        
        if (visited[u] == 0) {
            visited[u] = 1;
            parent[u] = curr.parent;
            
            // Duyệt từ n về 1 để khi pop ra, các đỉnh nhỏ hơn được xử lý trước
            for (int i = 1; i <= G->n; i++) {
                if (G->A[u][i] == 1 && visited[i] == 0) {
                    Element next = {i, u};
                    push(&s, next);
                }
            }
        }
    }
}

int main() {
    freopen("dt.txt", "r", stdin); // Nhớ gỡ khi nộp bài
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;
    
    Graph G;
    init_graph(&G, n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    int visited[105] = {0};
    int parent[105];
    for (int i = 1; i <= n; i++) parent[i] = 0;

    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            DFS(&G, i, visited, parent);
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", i, parent[i]);
    }
    return 0;
}