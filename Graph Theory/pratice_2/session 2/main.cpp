// Cho một đồ thị vô hướng đơn. Hãy in ra thứ tự của các đỉnh khi duyệt đồ thị theo chiều sâu (sử dụng NGĂN XẾP) bắt đầu từ đỉnh 1.

// Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

// Quy ước:

// Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần.


// Đầu vào (Input):
// Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

// - Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

// - m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

// Đầu ra (Output):

// In ra các đỉnh theo thứ tự duyệt, mỗi đỉnh trên 1 dòng.

// Xem thêm các ví dụ bên dưới.



// Hướng dẫn đọc dữ liệu và chạy thử chương trình
// Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
// Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
// Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
// 	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
// 	Graph G;
// 	int n, m, u, v, w, e;
// 	scanf("%d%d", &n, &m);
// 	init_graph(&G, n);
	
// 	for (e = 0; e < m; e++) {
// 		scanf("%d%d", &u, &v);
// 		add_edge(&G, u, v);
// 	}

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
        for(int v = G.n; v>=1;v--){
            if(G.A[u][v]&&visited[v]==0){
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