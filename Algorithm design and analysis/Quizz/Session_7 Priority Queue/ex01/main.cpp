#include<stdio.h>
#include<iostream>
using namespace std;

// function solve():
//     read n
//     read array A[1..n]

//     current_max = -infinity
//     for i = 1 to n:
//         current_max = max(current_max, A[i])

//     read q
//     for i = 1 to q:
//         read type

//         if type == 1:
//             read x
//             current_max = max(current_max, x)
//         else:  // type == 2
//             print current_max

void solve(){
    int n;
    cin>>n;
    int a[n+1];
    for(int i = 1;i<=n;i++){
        cin>>a[i];
    }
    int current_max = a[1];
    for(int i = 1;i<=n;i++){
        if(a[i]>current_max){
            current_max = a[i];
        }
    }

    int q;
    cin>>q;
    for(int i = 1; i<=q;i++){
        int type;
        cin>>type;
        if(type == 1){
            int x;
            cin>>x;
            if(x>current_max){
                current_max = x;
            }
        }
        else{
                cout<<current_max;
                cout<<endl;
        }
    }
}

int main(){
    freopen("ex01_04.inp","r",stdin);
    solve();
    return 0;
}