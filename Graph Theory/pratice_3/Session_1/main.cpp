#include<stdio.h>

#define MAXN 105
#define MAXM 505
#define INF 1000000000

typedef struct {
    int to;
    int w;
    int next;
} Edge;

typedef struct {
    int n;
    int head[MAXN];
    Edge edges[MAXM];
    int edgeCount;
} Graph;

void init_graph(Graph *G, int n) {
    G->n = n;
    G->edgeCount = 0;
    for (int i = 1; i <= n; i++)
        G->head[i] = -1;
}

void add_edge(Graph *G, int u, int v, int w) {
    G->edges[G->edgeCount].to = v;
    G->edges[G->edgeCount].w = w;
    G->edges[G->edgeCount].next = G->head[u];
    G->head[u] = G->edgeCount;
    G->edgeCount++;
}


// Hàm Dijkstra(G, n, m, source = 1, target = n):
//     // Khởi tạo
//     dist[1..n] = INF
//     dist[source] = 0
//     visited[1..n] = false

//     // Dùng priority queue (min-heap) chứa cặp (khoảng cách, đỉnh)
//     pq = priority_queue()
//     pq.push((0, source))

//     while pq không rỗng:
//         (d, u) = pq.pop_min()

//         if visited[u]:
//             continue
//         visited[u] = true

//         if u == target:
//             break   // có thể dừng sớm

//         for mỗi cung (u, v, w) trong danh sách kề của u:
//             if not visited[v] and dist[u] + w < dist[v]:
//                 dist[v] = dist[u] + w
//                 pq.push((dist[v], v))

//     if dist[target] == INF:
//         in ra -1
//     else:
//         in ra dist[target]
int dist[MAXN];
int visited[MAXN];

int dijkstra(Graph *G, int source, int target){
    int n = G->n;
    for(int i = 1; i<=n;i++){
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[source] = 0;
    for (int count = 1; count <= n; count++) {
        // Bước 1: tìm đỉnh u chưa thăm có dist[u] nhỏ nhất
        int u = -1;
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        // Nếu không tìm được đỉnh nào có thể đến -> dừng
        if (dist[u] == INF) break;

        visited[u] = 1;

        // Bước 2: cập nhật (relax) các đỉnh kề với u
        for (int e = G->head[u]; e != -1; e = G->edges[e].next) {
            int v = G->edges[e].to;
            int w = G->edges[e].w;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    if (dist[target] == INF) return -1;
    return dist[target];
}

int main(){
    // freopen("dt.txt", "r", stdin); // Khi nộp bài nhớ bỏ dòng này

    Graph G;
    int n, m, u, v, w, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int result = dijkstra(&G, 1, n);
    printf("%d\n", result);

    return 0;
}
