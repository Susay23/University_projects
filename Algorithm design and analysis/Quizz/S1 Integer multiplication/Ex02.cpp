#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef vector<int> BigInt;


void removeLeadingzero(BigInt& num){
    while(num.size()>1 && num.back() == 0){
        num.pop_back();
    }
}

BigInt StringToBigInt(const string& n){
    BigInt res;
    for(int i = n.size()-1; i >= 0; i--){
        res.push_back(n[i]-'0');
    }
    return res;
}

void PrintBigInt(BigInt& num){
    for(int i = num.size()-1; i>= 0; i--){
        cout << num[i];
    }
    cout << endl;
}

BigInt add(const BigInt& x, const BigInt& y){
    BigInt res(max(x.size(),y.size()),0);
    int carry = 0;
    for(int i = 0; i < res.size(); i++){
        int current_value = carry;
        if(i < x.size()) current_value += x[i];
        if(i < y.size()) current_value += y[i];
        res[i] = current_value%10;
        carry = current_value/10;
    }
    removeLeadingzero(res);
    return res;
}

BigInt mulby10power(const BigInt& num, int power){
    BigInt res(power,0);
    res.insert(res.end(), num.begin(), num.end());
    return res;
}

BigInt DAC_mul(const BigInt& x, const BigInt& y){
    if(x.size() == 0 || y.size() == 0 || (x.size() == 1 && x[0] == 0) || (y.size() == 1 && y[0] == 0)) return {0};
    if(x.size() == 1 && y.size() == 1) {
        int mul = x[0]*y[0];
        return {mul%10, mul/10};
    }
    int n = max(x.size(), y.size());
    int half = n/2;

    BigInt x_high(x.begin()+half, x.end());
    BigInt x_low(x.begin(), x.begin()+half);
    BigInt y_high(y.begin()+half, y.end());
    BigInt y_low(y.begin(), y.begin()+half);

    // ac*(10^(2*half)) + (ab+dc)*(10^half) + bd
    BigInt ac = DAC_mul(x_high, y_high);
    BigInt bd = DAC_mul(x_low, y_low);
    BigInt ab = DAC_mul(x_high, y_low);
    BigInt dc = DAC_mul(x_low, y_high);

    BigInt res = add(add(mulby10power(ac, 2*half), mulby10power(add(ab,dc), half)),bd);
    removeLeadingzero(res);
    return res;
}

int main(int argc, char *argv[]){
    if (argc < 2){
        cout << "Usage: " << argv[0] << " num1 num2" << endl;
        return 1;
    }
    FILE* f = fopen(argv[1], "r");
    if(!f){
        cout << "Cannot open file: " << argv[1] << endl;
        return 1;
    }
    char num1[1001], num2[1001];
    while(fscanf(f, "%s %s", num1, num2) == 2){
        BigInt x = StringToBigInt(num1);
        cout << "num1: ";
        PrintBigInt(x);
        cout << "x\n";
        BigInt y = StringToBigInt(num2);
        cout << "num2: ";
        PrintBigInt(y);
        cout << "=\n";
        BigInt result = DAC_mul(x,y);
        PrintBigInt(result);
        cout << "-------------------\n";
        cout << endl;
    }
    fclose(f);
    return 0;
}
