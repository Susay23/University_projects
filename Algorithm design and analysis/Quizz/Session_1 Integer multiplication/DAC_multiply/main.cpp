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

BigInt add(const BigInt &a, const BigInt &b){
    BigInt res(max(a.size(),b.size()),0);
    int carry = 0;
    for(int i = 0 ; i < res.size(); i ++){
        int sum = carry;
        if(i<a.size()) sum+=a[i];
        if(i<b.size()) sum+=b[i];
        res[i] = sum % 10;
        carry = sum / 10;
    }
    removeleadingzeros(res);
    return res;
}

BigInt mul10power(BigInt &a, int power){
    BigInt res(power,0);
    res.insert(res.end(),a.begin(),a.end());
    return res;
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

BigInt DAC_mul(BigInt &x, BigInt &y){
    if(x.size() == 0 || y.size() == 0 || (x.size() == 1 && x[0] == 0) || (y.size() == 1 && y[0] == 0)){
        return {0};
    }

    if(x.size() == 1 && y.size() == 1){
        int mul = (x[0]) * (y[0]);
        return {mul % 10, mul / 10};
    }


    int n = max(x.size(),y.size());
    int half = n/2;
    
    BigInt x_low(x.begin(),x.begin()+half);
    BigInt x_high(x.begin()+half,x.end());
    BigInt y_low(y.begin(),y.begin()+half);
    BigInt y_high(y.begin()+half,y.end());
    // (z2)*(10^2*half) + (z1a + z1b)*(10^half) + z0
    // zo = x_low * y_low, z1 = (x_low * y_high) + (x_high * y_low), và z2 = x_high * y_high

    BigInt z0 = DAC_mul(x_low, y_low);
    BigInt z1_a = DAC_mul(x_low,y_high);
    BigInt z1_b = DAC_mul(x_high,y_low);
    BigInt z1 = add(z1_a,z1_b);
    BigInt z2 = DAC_mul(x_high,y_high);

    BigInt part1 = mul10power(z2,2*half);
    BigInt part2 = mul10power(z1,half);
    BigInt res = add(add(part1,part2),z0);

    removeleadingzeros(res);
    return res;
}

int main(){
    freopen("ex01_02.inp", "r", stdin);
    char str1[100000];
    char str2[100000];
    cin >> str1;
    cin >> str2;
    BigInt a = StringToBigInt(str1);
    BigInt b = StringToBigInt(str2);

    BigInt result = DAC_mul(a,b);

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