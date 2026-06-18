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


// ALGORITHM InsertionSort(A, low, high)
    // Sắp xếp đoạn A[low..high] tăng dần
    
//     for i = low + 1 to high:
//         key = A[i]
//         j = i - 1
        
        // Dịch các phần tử lớn hơn key sang phải để tạo chỗ trống
//         while j >= low and A[j] > key:
//             A[j + 1] = A[j]
//             j = j - 1
        
//         A[j + 1] = key

void insertionSort(int A[], int low, int high) {
    for(int i = low + 1; i < high; i++){
        int key = A[i];
        int j = i -1;
        while(j>=low && A[j]>key){
            A[j+1] = A[j];
            j = j - 1;        
        }
        A[j+1] = key;
    }
}


// ALGORITHM FindIndex(A, low, high, value)
//     for i = low to high:
//         if A[i] == value:
//             return i
//     return -1    // không tìm thấy (không nên xảy ra nếu logic đúng)

int FindIndex(int A[], int low, int high, int Value){
    for(int i = low; i <= high; i ++){
        if(A[i] == Value){
            return 1;
        }
    }
    return -1;
}

// ALGORITHM Select(A, low, high, k)
    // Tìm phần tử nhỏ thứ k trong đoạn A[low..high]
//     n = high - low + 1

//     if n <= 5:
//         InsertionSort(A, low, high)      // sắp xếp trực tiếp đoạn nhỏ
//         return A[low + k - 1]

    // ----- Bước 1 & 2: Chia nhóm 5, tìm trung vị mỗi nhóm -----
//     numGroups = (n+4) / 5
//     medians = new array[numGroups]

//     for i = 0 to numGroups - 1:
//         groupLow  = low + i * 5
//         groupHigh = min(groupLow + 4, high)
//         InsertionSort(A, groupLow, groupHigh)
//         medianPos = groupLow + (groupHigh - groupLow) / 2
//         medians[i] = A[medianPos]

    // ----- Bước 3: Đệ quy tìm trung vị của các trung vị -----
//     pivotValue = Select(medians, 0, numGroups - 1, (numGroups + 1) / 2)

    // ----- Bước 4: Đưa pivotValue về cuối đoạn để Partition dùng -----
//     pivotIndex = FindIndex(A, low, high, pivotValue)
//     swap(A[pivotIndex], A[high])

//     newPivotIndex = Partition(A, low, high)   // giống Partition của Quickselect
//     rank = newPivotIndex - low + 1

    // ----- Bước 5: Đệ quy như Quickselect -----
//     if k == rank:
//         return A[newPivotIndex]
//     else if k < rank:
//         return Select(A, low, newPivotIndex - 1, k)
//     else:
//         return Select(A, newPivotIndex + 1, high, k - rank)

int Select(int A[], int low, int high, int k){
    int n = high - low + 1;

    if(n<=5){
        insertionSort(A, low, high);
        return A[low+k-1];
    }

    int numGroup = (n+4)/5;
    int* medians = new int[numGroup];

    for(int i = 0; i < numGroup - 1; i++){
        int grouplow = low+i*5;
        int grouphigh = min(grouplow+4,high);
        insertionSort(A,grouplow,grouphigh);
        int mediansPos = grouplow + (grouplow - grouphigh)/2;
        medians[i] = A[mediansPos]; 
    }

    int pivotval = Select(medians, 0, numGroup - 1, (numGroup + 1) / 2);

    int pivotIndex = FindIndex(A,low,high,pivotval);
    int temp = A[pivotIndex];
    A[pivotIndex] = A[high];
    A[high] = temp;

    int newPivotIndex = Partition(A,low,high);
    int rank = newPivotIndex - low + 1;

    if(k == rank){
        return A[newPivotIndex];
    }
    else if(k<rank){
        return Select(A,low,newPivotIndex - 1, k);
    }
    else{
        return Select(A,newPivotIndex+1,high,k-rank);
    }
}


// ALGORITHM FindKSmallestElements(A, n, k)
//     Select(A, 0, n - 1, k)
    // Sau khi gọi xong, A[0..k-1] chính là k phần tử nhỏ nhất (chưa chắc đã sắp theo thứ tự)
//     return A[0..k-1]

int FindKSmallestElements(int A[], int n, int k){
    if(k<1 || k>n){
        printf("Error!!!\n");
        return -1;
    }
    return Select(A,0,n-1,k);
}

int main(){
    freopen("ex02_01.inp", "r", stdin);
    int n;
    cin >> n;
    int A[n];
    for(int i = 0; i < n; i++){
        cin >> A[i];
    }
    int k;
    cin >> k;
    cout << FindKSmallestElements(A,n,k) << " \n";
}