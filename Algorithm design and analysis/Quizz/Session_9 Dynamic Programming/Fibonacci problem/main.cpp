#include<stdio.h>
#include<iostream>
#include <vector>
#include <chrono>

using namespace std;

// 1. Naive Recursion -> time complexity: O(2^n)
// function fib_naive(n):
//     if n <= 1: return n
//     return fib_naive(n-1) + fib_naive(n-2)

long long fib_native(int n){
    if(n<2){
        return n;
    }
    return fib_native(n-1) + fib_native(n-2);
}

// 2. Memoized DP -> time complexity: O(n)
// memo = array of size (n+1), filled with -1

// function fib_memo(n):
//     if n <= 1: return n
//     if memo[n] != -1: return memo[n]
//     memo[n] = fib_memo(n-1) + fib_memo(n-2)
//     return memo[n]
vector<long long> memo;
long long fib_memo(int n){
    if(n<2){
        return n;
    }
    if(memo[n]!=-1){
        return memo[n];
    }
    memo[n] = fib_memo(n-1) + fib_memo(n-2);
    return memo[n];
}

// 3. Bottom-up DP -> time complexity: O(n)
// function fib_bottomup(n):
//     if n <= 1: return n
//     prev2 = 0, prev1 = 1
//     for i from 2 to n:
//         curr = prev1 + prev2
//         prev2 = prev1
//         prev1 = curr
//     return prev1

long long fib_bottomup(int n){
    if(n<2){
        return n;
    }
    long long prev2 = 0, prev1 = 1;
    for(int i = 2; i<=n;i++){
        long long curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main(){
    freopen("ex01.inp","r",stdin);

    int n;
    while(scanf("%d", &n) == 1){   // đọc tới khi hết file
        printf("n = %d\n", n);

        // ---- Naive ----
        auto t1 = chrono::high_resolution_clock::now();
        long long r1 = fib_native(n);
        auto t2 = chrono::high_resolution_clock::now();
        double time_naive = chrono::duration<double, milli>(t2 - t1).count();

        // ---- Memoized ----
        memo.assign(n + 1, -1);   // resize + reset memo cho từng n
        auto t3 = chrono::high_resolution_clock::now();
        long long r2 = fib_memo(n);
        auto t4 = chrono::high_resolution_clock::now();
        double time_memo = chrono::duration<double, milli>(t4 - t3).count();

        // ---- Bottom-up ----
        auto t5 = chrono::high_resolution_clock::now();
        long long r3 = fib_bottomup(n);
        auto t6 = chrono::high_resolution_clock::now();
        double time_bottomup = chrono::duration<double, milli>(t6 - t5).count();

        printf("  Naive:     result=%lld  time=%.5f ms\n", r1, time_naive);
        printf("  Memo:      result=%lld  time=%.5f ms\n", r2, time_memo);
        printf("  BottomUp:  result=%lld  time=%.5f ms\n", r3, time_bottomup);
        printf("--------------------------------------\n");
    }

    return 0;
}