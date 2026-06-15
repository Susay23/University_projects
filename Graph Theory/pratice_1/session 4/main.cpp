#include<stdio.h>
#include<iostream>

using namespace std;

typedef struct {
    int A[100][100];
    int n;
} Graph;

// FUNCTION degreeMatrix(A[0..n-1][0..n-1], n):
//     FOR u = 0 TO n-1:
//         deg = 0
//         FOR v = 0 TO n-1:
//             deg = deg + A[u][v]   // mỗi A[u][v]=1 là 1 cạnh kề

int deg(Graph* G, int x){
    int deg = 0;
    for(int v = 0; v<G->n;v++){
        deg = deg + G->A[x][v];
    }
    return deg;
}

// FUNCTION deg2(G):
//     count = 0
//     FOR x = 1 TO G.n:
//         d = deg(G, x)          // tái dụng hàm deg đã có
//         IF d % 2 == 0:
//             count = count + 1
//     RETURN count

int deg2(Graph* G) {
    int count = 0;
    for(int i = 1; i < G->n; i++){
        int d = deg(G,i);
        if(d%2==0){
            count +=1;
        }
    }
    return count;
}

// FUNCTION deg3(G):
//     count = 0
//     FOR x = 1 TO G.n:
//         d = deg(G, x)          // tái dụng hàm deg đã có
//         IF d == 3:
//             count = count + 1
//     RETURN count

int deg3(Graph* G) {
    int count = 0;
    for(int i = 1; i< G ->n ;i++){
        int d = deg(G,i);
        if(d == 3){
            count+=1;
        }
    }
    return count;
}

int main(){
    FILE *f = fopen("dt1.txt", "r");

    int m,n;
    fscanf(f, "%d%d", &m, &n);

    int graph[m+1][n+1];
    for(int i=1; i<=m;i++){
        for(int j=1; j<=n;j++){
            graph[i][j] = 0;
        }
    }
    int up,down;
    for (int i=0; i<=m;i++){
        fscanf(f, "%d%d", &up, &down);
        if(up<=n && down<=n){
        graph[up][down] = 1;
        graph[down][up] = 1;
        }
    }
    Graph A;
    A.n = n;
    for(int i=1; i<=n;i++){
        for(int j=1; j<=n;j++){
            A.A[i][j] = graph[i][j];
        }
    }

    for(int i=1;i<n;i++){
        printf(" deg of %d: %d\n", i, deg(&A,i));
    }

    printf("deg 2 is: %d\n", deg2(&A));

    printf("deg 3 is: %d\n", deg3(&A));

    fclose(f);
    return 0;
}