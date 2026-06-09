#include<stdio.h>

int main(){
    FILE *f = fopen("dt1.txt", "r");

    int m,n;
    fscanf(f, "%d%d", &m, &n);

    int graph[m][n];
    for(int i=0; i<m;i++){
        for(int j=0; j<n;j++){
            graph[i][j] = 0;
        }
    }
    int up,down;
    for (int i=0; i<m;i++){
        fscanf(f, "%d%d", &up, &down);
        graph[up][down] = 1;
        graph[down][up] = 1;
    }
    
    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    fclose(f);
    return 0;
}