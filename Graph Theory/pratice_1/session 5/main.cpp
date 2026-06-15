#include<stdio.h>
#include<iostream>

using namespace std;

typedef struct {
    int A[100][100];
    int n;
} Graph;

// FUNCTION edgeCount(G):
//     count = 0
//     FOR i = 0 TO G.n-1:
//         FOR j = 0 TO G.n-1:
//             count = count + G.A[i][j]   // cộng trọng số, không chỉ đếm != 0

//     RETURN count / 2                    // vẫn chia 2 vì ma trận đối xứng

int edgeCount(Graph* G) {
    int count =0;
    for(int i =0;i<G->n;i++){
        for(int j=0; j<G->n;j++){
            if(G->A[i][j] !=0){
                count= count + G->A[i][j];
            }
        }
    }
    return count/2;
}

// Tại sao chia 2?
// Đồ thị vô hướng có ma trận kề đối xứng — cạnh (u, v) xuất hiện ở cả A[u][v] và A[v][u], nên tổng đếm được gấp đôi số cạnh thực.
// Ví dụ cạnh (1,2):
//   A[1][2] = 2  → đếm 1 lần
//   A[2][1] = 2  → đếm 1 lần
//               → thực ra chỉ 1 cạnh

int main(){
    freopen("dt1.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    Graph A;
    A.n = n;

    for(int i =0; i<n; i++){
        for(int j = 0; j<n;j++){
            scanf("%d", &A.A[i][j]);
        }
    }

    printf("edge is: %d", edgeCount(&A));

    return 0;
}
