#include<stdio.h>
#include<iostream>
#include <cstdlib>   // rand()
#include <ctime> 

using namespace std;

void gen_random(int D[], int n){
    srand(time(0));
    for (int i = 0; i < n; i++) {
        D[i] = rand() % 999 + 1;
    }
}

int partition(int A[], int low, int high){
    int pivot = A[high];
    int i = low - 1;
    for(int j =low; j<high;j++){
        if(A[j]<=pivot){
            i+=1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i+1];
    A[i+1] = A[high];
    A[high] = temp;
    return i + 1;
}

void quicksort(int A[], int low, int high){
    if(low<high){
        int p = partition(A,low,high);
        quicksort(A,low,p-1);
        quicksort(A,p+1,high);
    }
}

int get_rank(int D[], int n, int d){ // Complexity: O(log n) time, O(1) space.
    int lo = 0;
    int hi = n;

    while(lo<hi){
        int mid = (lo+hi)/2;
        if(D[mid]<d){
            lo = mid + 1;
        }else{
            hi = mid;
        }
    }
    return lo;
}

int upper_bound(int D[], int n, int d){ 
    int lo = 0;
    int hi = n;

    while(lo<hi){
        int mid = (lo+hi)/2;
        if(D[mid]<=d){
            lo = mid + 1;
        }else{
            hi = mid;
        }
    }
    return lo;
}

int count(int D[], int n, int d){ // Complexity: O(log n) time (two binary searches), O(1) space.
    return upper_bound(D,n,d) - get_rank(D,n,d);
}

int binarysearch(int x, int A[], int start, int end){ 
    while (start<=end)
    {
        int mid = (start + end)/2;
        if(A[mid] == x){
            return mid;
        }
        else if(A[mid]<x){
            start = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }
    return -1;
}

int main(){
    int n = 100;
    freopen("input.txt","r",stdin);
    cin >> n;
    int D[n];
    // gen_random(D, 100);
    for(int i = 0; i < n; i ++){
        cin >> D[i];
    }
    quicksort(D,0,n-1);

    for(int i = 0; i < n; i++){
        cout << D[i] << " ";
    }
    cout << " \n";

    int d;
    cout << "input rank d ";
    cin >> d;

    cout << "rank of " << d << " : " << binarysearch(d, D, 0, n) << "\n";
    // cout << "rank of " << d << " : " << get_rank(D, n, d) << "\n";

    cout << "competitions did she get a given score d is " << count(D, n ,d) << "\n";
    return 0;
}