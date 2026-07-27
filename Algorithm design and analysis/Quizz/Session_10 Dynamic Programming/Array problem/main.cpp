#include<stdio.h>
#include<iostream>
#include<chrono>
#include<vector>

using namespace std;
using namespace std::chrono;

// 1. Naive / Brute-force — O(n²)
// function maxSubarray_naive(a, n):
//     maxSum = -infinity
//     for i = 0 to n-1:
//         sum = 0
//         for j = i to n-1:
//             sum = sum + a[j]
//             if sum > maxSum:
//                 maxSum = sum
//                 start = i
//                 end = j
//     return maxSum, start, end
int n;
vector<long long> a;

void printSubarray(int start, int end) {
    for (int i = start; i <= end; i++) cout << a[i] << (i < end ? " " : "\n");
}

long long maxSubarray(int &start, int &end){
    long long maxSum = 0;
    for(int i=0; i<n;i++){
        long long sum = 0;
        for(int j = 0; j < n; j++){
            sum+=a[j];
            if(sum>maxSum){
                maxSum = sum;
                start = i;
                end = j;
            }
        }
    }
    return maxSum;
}

// 2. Memoized DP (Top-down) — O(n)
// memo = array size n, filled with UNCOMPUTED
// startAt = array size n   // lưu điểm bắt đầu của subarray tốt nhất kết thúc tại i

// function maxEndingAt(i):
//     if i == 0:
//         startAt[0] = 0
//         return a[0]
//     if memo[i] != UNCOMPUTED:
//         return memo[i]
//     prev = maxEndingAt(i-1)
//     if prev > 0:
//         memo[i] = prev + a[i]
//         startAt[i] = startAt[i-1]
//     else:
//         memo[i] = a[i]
//         startAt[i] = i
//     return memo[i]

// function maxSubarray_memo(a, n):
//     for i = 0 to n-1: maxEndingAt(i)   // đảm bảo memo[] đầy đủ
//     best = index of max value in memo[]
//     return memo[best], startAt[best], best   // (maxSum, start, end)

vector<long long> memo;
vector<int> startAt;
bool computed_flag;

long long maxEndingAt(int i){
    if(i==0){
        startAt[0] = 0;
        return a[0];
    }
    if(memo[i]!=0){
        return memo[i];
    }
    long long prev = maxEndingAt(i - 1);
    if(prev>0){
        memo[i] = prev + a[i];
        startAt[i] = startAt[i-1];
    }
    else{
        memo[i] = a[i];
        startAt[i] = i;
    }
    return memo[i];
}

long long maxSubarray_memo(int &start, int &end){
    memo.assign(n,0);
    startAt.assign(n, 0);
    for(int i = 0; i<n;i++){
        maxEndingAt(i);
    }
    long long best = 0;
    int bestIdx = 0;
    for(int i = 0; i<n;i++){
        if(memo[i]>best){
            best = memo[i];
            bestIdx = i;
        }
    }
    start = startAt[bestIdx];
    end = bestIdx;
    return best;
}

// 3. Bottom-up DP (chính là thuật toán Kadane) — O(n), O(1) không gian
// function maxSubarray_bottomup(a, n):
//     maxSum = a[0]
//     currentSum = a[0]
//     start = 0, end = 0, tempStart = 0

//     for i = 1 to n-1:
//         if currentSum > 0:
//             currentSum = currentSum + a[i]
//         else:
//             currentSum = a[i]
//             tempStart = i

//         if currentSum > maxSum:
//             maxSum = currentSum
//             start = tempStart
//             end = i

//     return maxSum, start, end

long long maxSubarray_bottomup(int &start, int &end){
    long long maxSum = a[0];
    long long currentSum = a[0];
    int tempStart = 0;
    start = 0;
    end = 0;
    
    for(int i = 1; i<n;i++){
        if (currentSum > 0) {
            currentSum += a[i];
        } else {
            currentSum = a[i];
            tempStart = i;
        }
        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            end = i;
        }
    }
    return maxSum;
}

int main() {
    freopen("ex03.inp", "r", stdin);
    cin >> n;
    a.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
 
    int start, end;
 
    // ---- 1. Naive ----
    auto t1 = high_resolution_clock::now();
    long long sumNaive = maxSubarray(start, end);
    auto t2 = high_resolution_clock::now();
    cout << "[Naive / Brute-force O(n^2)]\n";
    cout << "The maximum sum: " << sumNaive << "\n";
    cout << "The sub array: "; printSubarray(start, end);
    cout << "Time: " << duration<double, milli>(t2 - t1).count() << " ms\n\n";
 
    // ---- 2. Memoized ----
    auto t3 = high_resolution_clock::now();
    long long sumMemo = maxSubarray_memo(start, end);
    auto t4 = high_resolution_clock::now();
    cout << "[Memoized DP O(n)]\n";
    cout << "The maximum sum: " << sumMemo << "\n";
    cout << "The sub array: "; printSubarray(start, end);
    cout << "Time: " << duration<double, milli>(t4 - t3).count() << " ms\n\n";
 
    // ---- 3. Bottom-up (Kadane) ----
    auto t5 = high_resolution_clock::now();
    long long sumBU = maxSubarray_bottomup(start, end);
    auto t6 = high_resolution_clock::now();
    cout << "[Bottom-up DP - Kadane O(n)]\n";
    cout << "The maximum sum: " << sumBU << "\n";
    cout << "The sub array: "; printSubarray(start, end);
    cout << "Time: " << duration<double, milli>(t6 - t5).count() << " ms\n";
 
    return 0;
}