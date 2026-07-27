#include<stdio.h>
#include<iostream>

using namespace std;

const long long mod = 1000000007;
const long long maxn = 1000000;

long long fact[maxn+1];

void precompute(){
    fact[0] = 1;
    for(int i = 1; i <= maxn; i ++){
        fact[i] = (fact[i-1]*i)%mod;
    }
}

// MOD = 1_000_000_007
// MAXN = 100000

// fact = array[0..MAXN]
// fact[0] = 1
// for i = 1 to MAXN:
//     fact[i] = (fact[i-1] * i) mod MOD

// Trả lời từng truy vấn
// read T
// for each test case:
//     read n
//     print fact[n]
// Lưu ý quan trọng: fact[i-1] * i có thể vượt quá phạm vi int (giai thừa mod vẫn có thể là số ~10^9, nhân với i lên tới 10^5 → tích ~10^14) — bắt buộc dùng long long khi nhân trước khi lấy mod.

int main(){
    int t;
    freopen("ex04.inp", "r", stdin);
    precompute();
    cin >> t;

    for(int i = 0; i<t;i++){
        int n;
        cin >> n;
        cout << fact[n];
        if(i<t-1){
            cout << " ";
        }
        // cout << "\n";
    }
    return 0;
}