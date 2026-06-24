#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> BigInt;

void removeLeadingzeros(BigInt &num){
    while (num.size() > 1 && num.back() == 0)
    {
        num.pop_back();
    }
}

BigInt StringToInt(const string& str){
    BigInt res;
    for(int i = str.size() - 1; i>=0; i --){
        res.push_back(str[i]-'0');
    }
    return res;
}

void PrintBigInt(const BigInt &num){
    for(int i = num.size() - 1;i>=0;i--){
        cout << num[i];
    }
    cout << endl;
}


BigInt add(const BigInt &x, const BigInt &y){
    int carry;
    BigInt res(max(x.size(),y.size()),0);
    for(int i = 0; i < res.size(); i ++){
        int sum = carry;
        if(i<x.size()) sum += x[i];
        if(i<y.size()) sum += y[i];
        res[i] = sum%10;
        carry = sum/10;
    }
    removeLeadingzeros(res);
    return res;
}


BigInt sub(const BigInt &x, const BigInt &y){
    int borrow = 0;
    BigInt res(x.size(),0);
    for(size_t i = 0; i < x.size(); i ++){
        int diff = x[i] - borrow;
        if(i<y.size()) diff -= y[i];
        if(diff<0){
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
    }
    removeLeadingzeros(res);
    return res;
}

BigInt mul10power(BigInt &x, int power){
    BigInt res(power,0);
    res.insert(res.end(), x.begin(),x.end());
    return res;
}


BigInt karasubat_multiply(BigInt &x, BigInt &y){
    if(x.size() == 0 || y.size() == 0 || (x.size() == 1 && x.back() == 0) || (y.size() == 1 && y.back() == 0)) return {0};

    if(x.size() == 1 && y.size() == 1){
        int mul = x[0]*y[0];
        return {mul%10, mul/10};
    }
    

    int n = max(x.size(),y.size());
    int half = n/2;

    BigInt x_low(x.begin(), x.begin()+half);
    BigInt x_high(x.begin()+half, x.end());
    BigInt y_low(y.begin(),y.begin() + half);
    BigInt y_high(y.begin()+half,y.end());
    // Tính z1 = z1_full - z2 - z0, theo công thức z1 = (x_high + x_low) * (y_high + y_low) - x_high * y_high - x_low * y_low, 
    // z0 = x_low * y_low
    // z1a = x_high + x_low
    // z1b = y_high + y_low
    // Tính z1_full = (x_high + x_low) * (y_high + y_low)
    // Tính z2 = x_high * y_high
    // result = (z2 * 10^(2*n/2)) + (z1 * 10^(n/2)) + z0

    BigInt z0 = karasubat_multiply(x_low,y_low);
    BigInt z1a = add(x_high,x_low);
    BigInt z1b = add(y_high,x_low);
    BigInt z1full = karasubat_multiply(z1a,z1b);
    BigInt z2 = karasubat_multiply(x_high,y_high);

    BigInt z1 = sub(sub(z1full,z2),z0);
    BigInt part1 = mul10power(z2,2*half);
    BigInt part2 = mul10power(z1, half);
    BigInt res = add(add(part1,part2),z0);

    removeLeadingzeros(res);
    return res;
}


int main(){
    freopen("Ex01_03.inp", "r", stdin);
    string str1, str2;
    cin >> str1;
    cin >> str2;

    BigInt a = StringToInt(str1);
    BigInt b = StringToInt(str2);
    BigInt result = karasubat_multiply(a,b);
    cout << "------------------------------------------" << endl;
    PrintBigInt(a);
    cout << "x ";
    PrintBigInt(b);
    cout << "------------------------------------------" << endl;
    cout << "Ket qua: ";
    PrintBigInt(result);
 
    return 0;
    
}
