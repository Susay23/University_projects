#include<stdio.h>
#include<algorithm>
#include<iostream>


using namespace std;

const int maxn = 100000;
int s[maxn], f[maxn];
int idx[maxn];
int selected[maxn];
int selectedcount;

bool cmp(int a, int b){
    return f[a]<f[b];
}


// function maxCompatibleRequests(s[1..n], f[1..n]):
//     // Tạo mảng index và sort theo f tăng dần
//     idx = [1, 2, ..., n]
//     sort idx by f[idx] increasing

//     count = 0
//     lastFinish = -infinity   // thời gian kết thúc của request đã chọn gần nhất

//     for i in idx (theo thứ tự đã sort):
//         if s[i] >= lastFinish:
//             // request i tương thích, chọn nó
//             count = count + 1
//             lastFinish = f[i]

//     return count

int maxCompatibleRequests(int n){
    for(int i = 0; i<n;i++){
        idx[i]=i;
    }
    sort(idx,idx+n,cmp);

    selectedcount = 0;
    int lastfinish = -1;
    for(int k = 0; k<n;k++){
        int i = idx[k];
        if(s[i]>=lastfinish){
            selected[selectedcount] = i;
            selectedcount+=1;
            lastfinish = f[i];
        }
    }
    return selectedcount;
}

int main(){
    freopen("ex01.inp","r",stdin);
    int n;
    cin >> n;
    for(int i = 0; i<n;i++){
        cin >> s[i];
    }

    for(int i = 0; i<n;i++){
        cin >> f[i];
    }

    int count = maxCompatibleRequests(n);

    cout << "max compatible resquests: " << count << "\n";

    for(int k = 0; k<count; k ++){
        int i = selected[k];
        cout << "request " << k + 1 << ": [" << s[i] << "," << f[i] << "]\n"; 
    }

    return 0;
}