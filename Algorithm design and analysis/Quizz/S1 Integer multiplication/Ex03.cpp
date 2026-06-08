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
    if(carry) res.push_back(carry);
    removeLeadingzero(res);
    return res;
}

BigInt mulby10power(const BigInt& num, int power){
    BigInt res(power,0);
    res.insert(res.end(), num.begin(), num.end());
    return res;
}

BigInt sub(const BigInt& x, const BigInt& y){
    BigInt res(x.size(),0);
    int borrow = 0;
    for(size_t i = 0; i<x.size();i++){
        int diff = x[i] - borrow;
        if(i<y.size()){
            diff -= y[i];
        }
        if(diff<0){
            diff+=10;
            borrow = 1;
        } else{
            borrow = 0;
        }
        res[i]=diff;
    }
    removeLeadingzero(res);
    return res;
}

BigInt Karasubat_mul(const BigInt& x, const BigInt& y){
    if(x.size() == 0 || y.size() == 0 || (x.size() == 1 && x[0] == 0) || (y.size() == 1 && y[0] == 0)) return {0};
    if(x.size() == 1 && y.size() == 1) {
        int mul = x[0]*y[0];
        if(mul < 10) return {mul};
        return {mul%10, mul/10};
    }
    int n = max(x.size(), y.size());
    int half = n/2;
    int half_x = min(half, (int)x.size());
    int half_y = min(half, (int)y.size());

    BigInt x_high(x.begin()+half_x, x.end());
    BigInt x_low(x.begin(), x.begin()+half_x);
    BigInt y_high(y.begin()+half_y, y.end());
    BigInt y_low(y.begin(), y.begin()+half_y);

    // z2*(10^(2*half)) + (z1)*(10^half) + z0
    // z1 = z1_full - z2 - z0
    BigInt z2 = Karasubat_mul(x_high, y_high);
    BigInt z0 = Karasubat_mul(x_low, y_low);
    //z1_full = z1a = add(x_high,y_low);
    BigInt z1a = add(x_high,x_low);
    BigInt z1b = add(y_high,y_low);
    BigInt z1_full = Karasubat_mul(z1a,z1b);
    BigInt z1 = sub(sub(z1_full,z2),z0);

    BigInt part_1 = mulby10power(z2,2*half);
    BigInt part_2 = mulby10power(z1, half);
    BigInt res = add(add(part_1,part_2), z0);

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
        BigInt result = Karasubat_mul(x,y);
        PrintBigInt(result);
        cout << "-------------------\n";
        cout << endl;
    }
    fclose(f);
    return 0;
}
