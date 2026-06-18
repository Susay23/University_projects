#include<stdio.h>
#include<iostream>

using namespace std;


// ALGORITHM Partition(A, low, high)
//     pivot = A[high]          // chọn phần tử cuối làm pivot
//     i = low - 1
    
//     for j = low to high - 1:
//         if A[j] <= pivot:
//             i = i + 1
//             swap(A[i], A[j])
    
//     swap(A[i + 1], A[high])
//     return i + 1

int Partition(int A[], int low, int high){
    int pivot = A[high];
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(A[j]<=pivot){
            i+=1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp_k = A[i+1];
    A[i+1] = A[high];
    A[high] = temp_k;
    return i + 1;
}

// ALGORITHM QuickSelect(A, low, high, k)
    // A: mảng, low/high: chỉ số đầu/cuối của đoạn đang xét
    // k: thứ tự cần tìm (k nhỏ nhất, k tính từ 1)
    
//     if low == high:
//         return A[low]
    
//     pivotIndex = Partition(A, low, high)
    
    // Tính vị trí của pivot trong toàn mảng (thứ tự nhỏ thứ mấy)
//     rank = pivotIndex - low + 1
    
//     if k == rank:
//         return A[pivotIndex]
//     else if k < rank:
//         return QuickSelect(A, low, pivotIndex - 1, k)
//     else:
//         return QuickSelect(A, pivotIndex + 1, high, k - rank)


int QuickSelect(int A[], int low, int high, int k){
    if(low == high){
        return A[low];
    }

    int pivotIndex = Partition(A, low, high);

    int rank = pivotIndex - low + 1;

    if(k==rank){
        return A[pivotIndex];
    }
    else if(k<rank){
        return QuickSelect(A,low,pivotIndex-1,k); 
    }
    else{
        return QuickSelect(A,pivotIndex+1,high,k-rank);
    }
}

// Gọi hàm chính
// ALGORITHM FindKSmallest(A, n, k)
//     if k < 1 or k > n:
//         error "k không hợp lệ"
//     return QuickSelect(A, 0, n - 1, k)

int FindSmallest(int A[], int n, int k){
    if(k<1 || k>n){
        printf("Error!!!\n");
        return -1;
    }
    return QuickSelect(A,0,n-1,k);
}

int main(){
    freopen("ex01_01.inp", "r", stdin);

    int n;
    cin >> n;
    int A[n];
    for(int i = 0; i<n;i++){
        cin >> A[i];
    }
    int k;
    cin >> k;
    int result = FindSmallest(A, n, k);
    if(result != -1){
    printf("%d\n", result);
    }
}