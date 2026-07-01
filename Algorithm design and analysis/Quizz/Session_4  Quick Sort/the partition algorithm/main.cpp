#include<stdio.h>
#include<iostream>
#include <vector>

using namespace std;

int swapcount_lomuto = 0;
int swapcount_hoare = 0;
int Partition_lomuto(int A[], int low, int high){
    int pivot = A[high];
    int i = low - 1;
    for(int j = low; j < high; j ++){
        if(A[j]<=pivot){
            i+=1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            swapcount_lomuto++;
        }
    }
    int temp_1 = A[i+1];
    A[i+1]=A[high];
    A[high]=temp_1;
    swapcount_lomuto++;
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
        swapcount_hoare++;
    }
}

void quicksort_2(int A[], int low, int high){
    if(low < high){
        int p = Partition_hoare(A,low,high);
        quicksort_2(A,low,p);
        quicksort_2(A,p+1,high);
    }
}

void quicksort_1(int A[], int low, int high){
    if(low < high){
        int p = Partition_lomuto(A,low,high);
        quicksort_1(A,low,p-1);
        quicksort_1(A,p+1,high);
    }
}

void printArray(int A[], int n){
    for(int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

int main(){
    freopen("ex01.inp", "r", stdin);
    
    int n;
    cin >> n;

    // Đổi VLA thành vector
    vector<int> A(n), B(n);

    for(int i = 0; i < n; i++){
        cin >> A[i];
        B[i] = A[i];  // copy sang B ngay từ đầu
    }

    // --- Lomuto ---
    cout << "Truoc: ";
    for(int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;

    quicksort_1(A.data(), 0, n-1);

    cout << "Sau:   ";
    for(int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;

    cout << "Swap Count in lomuto: " << swapcount_lomuto << endl;

    // --- Hoare ---
    // BỎ vòng cin >> B[i] ở đây, B đã có dữ liệu từ đầu

    cout << "Truoc: ";
    for(int i = 0; i < n; i++) cout << B[i] << " ";
    cout << endl;

    quicksort_2(B.data(), 0, n-1);

    cout << "Sau:   ";
    for(int i = 0; i < n; i++) cout << B[i] << " ";
    cout << endl;

    cout << "Swap Count in hoare: " << swapcount_hoare << endl;

    return 0;
}