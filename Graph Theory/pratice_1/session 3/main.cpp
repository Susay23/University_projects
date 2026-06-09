#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
ElementType data[MAX_ELEMENTS];
int size;
} List;

void push_back(List* L, ElementType x) {
L->data[L->size] = x;
L->size++;
}

typedef struct {
    int A[100][500];
    int m, n;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void add_edge(Graph* G, int e, int x, int y){
    if(x<1 || x>G->m || y<1 || y>G->n) {
        return;
    }
    if(x==y){
        G->A[x][e] = 2;
    } else {
        G->A[x][e] = 1;
        G->A[y][e] = 1;
    }
    G->m++;
}

int deg(Graph* G, int x){
    if(x<1 || x>G->m) {
        return -1;
    }
    int degree = 0;
    for(int i=1; i<=G->m; i++){
        if(G->A[x][i] == 1){
            degree++;
        } else if(G->A[x][i] == 2){
            degree += 2;
        }
    }
    return degree;
}


List neighbors(Graph* G, int x){
    int const DEBUG = 0;
    if (DEBUG) printf("x = %d\n",x);
    List L;
    L.size =0;
    // moi cung c cua G
    for(int i = 0; i<G->m;i++){
        if (DEBUG) printf("Xet cung %d: ",i);
        //dinh x la 1 dau cua c
        if (G->A[x][i] == 1){
            if (DEBUG) printf("co dinh %d, ",x);
            for(int j =1;j<=G->n;j++) if (DEBUG) printf("%d",G->A[j][i] );
            //= tim dinh con lai cua c;
            for(int j =1;j<=G->n;j++){
                if(G->A[j][i]==1 && j !=x){
                    push_back(&L, j);
                    if (DEBUG) printf(" Them dinh %d",j);
                    break;
                }
            }
            
        }
        if (DEBUG) printf("\n");
    }
    
    return L;
}

int main(){ // test all functions
    Graph G;
    init_graph(&G, 5);
    add_edge(&G, 1, 1, 2);
    add_edge(&G, 2, 1, 3);
    add_edge(&G, 3, 2, 4);
    add_edge(&G, 4, 3, 4);
    add_edge(&G, 5, 4, 5);
    add_edge(&G, 6, 5, 1);
    printf("Degree of vertex 1: %d\n", deg(&G, 1));
    printf("Degree of vertex 2: %d\n", deg(&G, 2));
    printf("Degree of vertex 3: %d\n", deg(&G, 3));
    printf("Degree of vertex 4: %d\n", deg(&G, 4));
    printf("Degree of vertex 5: %d\n", deg(&G, 5));

    List neighbors_of_1 = neighbors(&G, 1);
    printf("Neighbors of vertex 1: ");
    for (int i = 0; i < neighbors_of_1.size; i++) {
        printf("%d ", neighbors_of_1.data[i]);
    }
    printf("\n");

    List neighbors_of_2 = neighbors(&G, 2);
    printf("Neighbors of vertex 2: ");
    for (int i = 0; i < neighbors_of_2.size; i++) {
        printf("%d ", neighbors_of_2.data[i]);
    }
    printf("\n");

    List neighbors_of_3 = neighbors(&G, 3);
    printf("Neighbors of vertex 3: ");
    for (int i = 0; i < neighbors_of_3.size; i++) {
        printf("%d ", neighbors_of_3.data[i]);
    }
    printf("\n");

    List neighbors_of_4 = neighbors(&G, 4);
    printf("Neighbors of vertex 4: ");
    for (int i = 0; i < neighbors_of_4.size; i++) {
        printf("%d ", neighbors_of_4.data[i]);
    }
    printf("\n");

    List neighbors_of_5 = neighbors(&G, 5);
    printf("Neighbors of vertex 5: ");
    for (int i = 0; i < neighbors_of_5.size; i++) {
        printf("%d ", neighbors_of_5.data[i]);
    }
    printf("\n");
    
}
