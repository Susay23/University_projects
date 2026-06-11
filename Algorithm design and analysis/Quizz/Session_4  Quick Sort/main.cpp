#include<stdio.h>
#include<iostream>

using namespace std;

int Partition_lomuto(int A[], int low, int high){
    int pivot = A[high];
    int i = low - 1;
    for(int j = low; j < high; j ++){
        if(A[j]<=pivot){
            i+=1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp_1 = A[i+1];
    A[i+1]=A[high];
    A[high]=temp_1;
    return i+1;
}

int Partition_hoare(int A[], int low, int high){
    int pivot = A[low];
    int i = low - 1;
    int j = high + 1;
    while(true){
        do {i+=1;
        } while (A[i]<pivot);
        do{
            j-=1;
        } while(A[j]>pivot);
        if(i>=j){
            return j;
        }
        int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
    }
}

void quicksort(int A[], int low, int high){
    if(low < high){
        int p = Partition_hoare(A,low,high);
        quicksort(A,low,p);
        quicksort(A,p+1,high);
    }
}

// void quicksort(int A[], int low, int high){
//     if(low < high){
//         int p = Partition_lomuto(A,low,high);
//         quicksort(A,low,p-1);
//         quicksort(A,p+1,high);
//     }
// }

void printArray(int A[], int n){
    for(int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

int main(){
    // Test 1: mảng bình thường
    int a[] = {3, 6, 8, 10, 1, 2, 1};
    int n = sizeof(a) / sizeof(a[0]);
    cout << "Truoc: "; printArray(a, n);
    quicksort(a, 0, n-1);
    cout << "Sau:   "; printArray(a, n);

    // Test 2: mảng đã sorted
    int b[] = {1, 2, 3, 4, 5};
    int m = sizeof(b) / sizeof(b[0]);
    cout << "\nTruoc: "; printArray(b, m);
    quicksort(b, 0, m-1);
    cout << "Sau:   "; printArray(b, m);

    // Test 3: mảng reverse sorted
    int c[] = {5, 4, 3, 2, 1};
    int k = sizeof(c) / sizeof(c[0]);
    cout << "\nTruoc: "; printArray(c, k);
    quicksort(c, 0, k-1);
    cout << "Sau:   "; printArray(c, k);

    // Test 4: mảng 1 phần tử
    int d[] = {42};
    cout << "\nTruoc: "; printArray(d, 1);
    quicksort(d, 0, 0);
    cout << "Sau:   "; printArray(d, 1);

    return 0;
}