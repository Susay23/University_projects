#include<stdio.h>

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
    
    for(int i=1; i<=n;i++){
        for(int j=1; j<=n;j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    fclose(f);
    return 0;
}