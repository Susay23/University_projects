#include <stdio.h>

typedef struct
{
    int A[101][101];
    int n;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            G->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int u, int v)
{
    G->A[u][v] = 1;
    G->A[v][u] = 1;
}

void DFS(Graph *G, int start, int visited[])
{
    visited[start] = 1;
    int visitedAll = 0;
    for (int i = 1; i <= G->n; i++)
    {
        if (G->A[start][i] == 1 && visited[i] == 0)
        {
            DFS(G, i, visited);
            visitedAll = 1;
        }
    }
}

int main()
{
    freopen("dt.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    int u, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    int visited[101];
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            DFS(&G, i, visited);
        }
    }
    int visitedAll = 1;
    for(int i = 1; i<=n;i++){
        if(visited[i] == 0){
            visitedAll = 0;
            break;
        }
    }
    if(visitedAll == 1){
        printf("YES\n");
    }else{
        printf("NO");
    }
}