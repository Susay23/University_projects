#include <stdio.h>

typedef struct
{
    int a[100][100];
    int n;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
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

int DFS_cycle(Graph *G, int start, int visited[], int parent[])
{
    visited[start] = 1;
    for (int i = 1; i <= G->n; i++)
    {
        if (G->a[start][i] == 1)
        {
            if(!visited[i]){
                parent[i] = start;
                if(DFS_cycle(G,i,visited,parent)){
                    return 1;
                }
            }else if(i!=parent[start]){
                return 1;
            }
        }
    }
    return 0;
}

int has_cycle(Graph *G){
    int visited[101] = {0};
    int parent[100];
    for(int i = 0; i<100;i++){
        parent[i] = -1;
    }
    for(int i = 1; i<=G->n; i++){
        if(!visited[i]){
            if(DFS_cycle(G,i,visited,parent)){
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
    int n, m, u, v, w, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    int visited[101] = {0};
    int parent[100];

    if(has_cycle(&G)){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    return 0;
}