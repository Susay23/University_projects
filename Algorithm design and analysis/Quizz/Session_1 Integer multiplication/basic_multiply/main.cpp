#include <stdio.h>
#include <iostream>
#include <vector>
#include<string>
using namespace std;

typedef vector<int> BigInt;

void removeleadingzeros(BigInt &num){
    while(num.size()>1 && num.back()==0){
        num.pop_back();
    }
}


BigInt StringToBigInt(const string& str){
    BigInt res;
    for(int i = str.size()-1; i >= 0; i--){
        res.push_back(str[i] - '0');
    }
    return res;
}


void printBigInt(BigInt &num){
    for(int i = num.size() - 1; i >= 0 ;i--){
        cout << num[i];
    }
    cout<<endl;
}

BigInt Basic_mul(BigInt &x, BigInt &y){
    BigInt res(x.size()+y.size(),0);
    for(int i = 0; i < x.size();i++){
        int carry = 0;
        for(int j = 0; j < y.size();j++){
            int current_val = res[i+j] + x[i]*y[j] + carry;
            res[i+j] = current_val%10;
            carry = current_val/10;
        }
        res[i + y.size()] += carry;
    }
    removeleadingzeros(res);
    return res;
}

int main(){
    freopen("ex01_01.inp", "r", stdin);
    char str1[100000];
    char str2[100000];
    cin >> str1;
    cin >> str2;
    BigInt a = StringToBigInt(str1);
    BigInt b = StringToBigInt(str2);

    BigInt result = Basic_mul(a,b);

    cout << "x: ";
    printBigInt(a);
    cout << "x";
    cout << "\n";
    cout << "y: ";
    printBigInt(b);
    cout << "\n";
    cout << "---------------------";
    cout << "\n";
    cout << "result: ";
    printBigInt(result);
    return 0;
}