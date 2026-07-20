Hãy hoàn thiện chương trình sau để đếm số thành phần liên thông của đồ thị vô hướng. Hãy copy đoạn chương trình của bạn và dán vào ô trả lời.

Chú ý: Biểu diễn đồ thị bằng phương pháp ma trận kề.

/*===BAT DAU==*/
Viết chương trình của bạn ở đây và copy phần này dán vào ô trả lời.
/*===KET THUC==*/
int main() {
    Graph G;
    int m, n, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (e = 1; e <= m; e++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G.A[u][v] = G.A[v][u] = 1;
    }
    
    printf("%d\n", connected_components(&G));
    return 0;
}