#include <stdio.h>

typedef struct
{
    int a[101][101];
    int n;
    int has_loop;
    int has_multi;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->has_loop = 0;
    G->has_multi = 0;
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
    if (u == v)
    {
        G->has_loop = 1;
        return;
    }
    if (G->a[u][v] == 1)
    {
        G->has_multi = 1;
    }
    G->a[u][v] = 1;
    G->a[v][u] = 1;
}

// DFS_CYCLE(G, start, visited[], parent[]):
//     visited[start] = 1
//     for i = 1..G.n:
//         if G.a[start][i] == 1:
//             if not visited[i]:
//                 parent[i] = start
//                 if DFS_CYCLE(G, i, visited, parent):
//                     return 1
//             else if i != parent[start]:
//                 return 1
//     return 0

int DFS_cycle(Graph *G, int start, int visited[], int parent[])
{
    visited[start] = 1;
    for (int i = 1; i <= G->n; i++)
    {
        if (G->a[start][i] == 1)
        {
            if (!visited[i])
            {
                parent[i] = start;
                if (DFS_cycle(G, i, visited, parent))
                {
                    return 1;
                }
            }
            else if (i != parent[start])
            {
                return 1;
            }
        }
    }
    return 0;
}

// HAS_CYCLE(G):
//     if G.has_loop == 1 or G.has_multi == 1:
//         return 1                    // phat hien truoc, khong can DFS
//     visited[1..n] = 0
//     parent[1..n] = -1
//     for i = 1..G.n:
//         if not visited[i]:
//             if DFS_CYCLE(G, i, visited, parent):
//                 return 1
//     return 0

int Has_cycle(Graph *G)
{
    if (G->has_loop == 1 || G->has_multi == 1)
    {
        return 1;
    }
    int visited[101] = {0};
    int parent[101];
    for (int i = 0; i <= G->n; i++)
    {
        parent[i] = -1;
    }
    for (int i = 1; i <= G->n; i++)
    {
        if (!visited[i])
        {
            if (DFS_cycle(G, i, visited, parent))
            {
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    freopen("dt.txt", "r", stdin); // Khi nộp bài nhớ bỏ dòng này.
    Graph G;
    int n, m, u, v, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    if (Has_cycle(&G))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}