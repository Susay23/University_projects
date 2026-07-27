#include<stdio.h>
#include<iostream>
#include<vector>
#include<chrono>

using namespace std;
using namespace std::chrono;

// 1. Naive Recursion -> time complexity: O(2^n).
// knap(i, W):
//     if i == 0 or W == 0: return 0
//     if w[i] > W: return knap(i-1, W)              // không chọn được item i
//     return max( knap(i-1, W),                      // không chọn item i
//                 p[i] + knap(i-1, W - w[i]) )        // chọn item i

// function buildSolution():
//     cap = W
//     for i = n downto 1:
//         if knap(i, cap) != knap(i-1, cap):
//             solution[i] = 1
//             cap = cap - w[i]
//         else:
//             solution[i] = 0


int W,n;
vector<int> w, p;
long long knap(int i, int cap){
    if(i==0 || cap == 0){
        return 0;
    }
    if(w[i] > cap){
        return knap(i-1,cap);
    }
    return max(knap(i-1,cap),p[i]+knap(i-1,cap - w[i]));
}

vector<int> solutionKnap(){
    vector<int> sol(n + 1, 0);
    int cap = W;

    for(int i = n; i >= 1; i--){
        if(knap(i,cap)!=knap(i-1,cap)){
            sol[i] = 1;
            cap-=w[i];
        }
    }
    return sol;
}

// 2. Memoized DP

// memo = table (n+1) x (W+1), filled with -1

// knap_memo(i, W):
//     if i == 0 or W == 0: return 0
//     if memo[i][W] != -1: return memo[i][W]
//     if w[i] > W: memo[i][W] = knap_memo(i-1, W)
//     else: memo[i][W] = max(knap_memo(i-1, W), p[i] + knap_memo(i-1, W-w[i]))
//     return memo[i][W]

// function buildSolution():
//     cap = W
//     for i = n downto 1:
//         if memo[i][cap] != memo[i-1][cap]:
//             solution[i] = 1
//             cap = cap - w[i]
//         else:
//             solution[i] = 0

vector<vector<long long>> memo;

long long knap_memo(int i, int cap){
    if(i == 0 || cap == 0){
        return 0;
    }
    if(memo[i][cap]!=-1){
        return memo[i][cap];
    }
    if(w[i] > cap){
        memo[i][cap] = knap_memo(i-1, cap);
    }
    else {
        memo[i][cap] = max(knap_memo(i-1, cap),p[i]+knap_memo(i-1,cap - w[i]));
    }
    return memo[i][cap];
}

vector<int> solutionKnap_memo(){
    vector<int> sol(n + 1, 0);
    int cap = W;
    for(int i = n; i >=1;i--){
        if(memo[i][cap]!=memo[i-1][cap]){
            sol[i] = 1;
            cap-=w[i];
        }else{
            sol[i] = 0;
        }
    }
    return sol;
}

// 3. Bottom-up DP
// dp[0][*] = 0, dp[*][0] = 0
// for i = 1 to n:
//     for w = 0 to W:
//         if weight[i] > w: dp[i][w] = dp[i-1][w]
//         else: dp[i][w] = max(dp[i-1][w], p[i] + dp[i-1][w - weight[i]])


// function buildSolution():
//     cap = W
//     for i = n downto 1:
//         if dp[i][cap] != dp[i-1][cap]:
//             solution[i] = 1
//             cap = cap - w[i]
//         else:
//             solution[i] = 0

vector<vector<long long>> dp;

long long knapbottomDP(){
    dp.assign(n + 1, vector<long long>(W + 1, 0));
    for(int i = 1; i<=n;i++){
        for(int cap = 0; cap <= W; cap ++){
            if(w[i]>cap){
                dp[i][cap] = dp[i-1][cap];
            }else{
                dp[i][cap] = max(dp[i-1][cap], p[i]+dp[i-1][cap - w[i]]);
            }
        }
    }
    return dp[n][W];
}


vector<int> solutionKnap_bottomdp(){
    vector<int> sol(n + 1, 0);
    int cap = W;
    for(int i = n; i>=1;i--){
        if(dp[i][cap]!=dp[i-1][cap]){
            sol[i] = 1;
            cap-=w[i];
        }else{
            sol[i] = 0;
        }
    }
    return sol;
}


void printSolution(const vector<int>& sol) {
    for (int i = 1; i <= n; i++) cout << sol[i] << (i < n ? " " : "\n");
}

int main() {
    freopen("ex02.inp", "r", stdin);
    cin >> n >> W;
    w.assign(n + 1, 0);
    p.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= n; i++) cin >> p[i];
 
    cout << "n=" << n << " W=" << W << "\n\n";
 
    // ---- 1. Naive ----
    auto t1 = high_resolution_clock::now();
    long long profitNaive = knap(n, W);
    vector<int> solNaive = solutionKnap();
    auto t2 = high_resolution_clock::now();
    cout << "[Naive Recursion]\n";
    cout << "Total profit: " << profitNaive << "\n";
    cout << "Solution: "; printSolution(solNaive);
    cout << "Time: " << duration<double, milli>(t2 - t1).count() << " ms\n\n";

    // ---- 2. Memoized ----
    memo.assign(n + 1, vector<long long>(W + 1, -1));
    auto t3 = high_resolution_clock::now();
    long long profitMemo = knap_memo(n, W);
    vector<int> solMemo = solutionKnap_memo();
    auto t4 = high_resolution_clock::now();
    cout << "[Memoized DP]\n";
    cout << "Total profit: " << profitMemo << "\n";
    cout << "Solution: "; printSolution(solMemo);
    cout << "Time: " << duration<double, milli>(t4 - t3).count() << " ms\n\n";

    // ---- 3. Bottom-up ----
    auto t5 = high_resolution_clock::now();
    long long profitBU = knapbottomDP();
    vector<int> solBU = solutionKnap_bottomdp();
    auto t6 = high_resolution_clock::now();
    cout << "[Bottom-up DP]\n";
    cout << "Total profit: " << profitBU << "\n";
    cout << "Solution: "; printSolution(solBU);
    cout << "Time: " << duration<double, milli>(t6 - t5).count() << " ms\n";

 
    return 0;
}