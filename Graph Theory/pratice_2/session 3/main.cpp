#include <stdio.h>

typedef struct
{
    int a[101][101];
    int n;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            G->a[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int u, int v)
{
    G->a[u][v] = 1;
    G->a[v][u] = 1;
}

void DFS(Graph G, int start, int visited[])
{
    visited[start] = 1;
    printf("visited %d \n", start);
    for (int i = 1; i <= G.n; i++)
    {
        if (G.a[start][i] == 1 && visited[i] == 0)
        {
            DFS(G, i, visited);
        }
    }
}

int main()
{
    int n, m;
    freopen("dt.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);
    G.n = n;

    int u, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    int visited[105] = {0};
    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            DFS(G, i, visited);
        }
    }
}