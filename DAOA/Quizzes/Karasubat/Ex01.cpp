#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

typedef vector<int> BigInt;

BigInt StingToBigInt(const string& s){ // convent String type to BigInt type
    BigInt res;
    for(int i=s.length()-1; i>=0;i--){  
        res.push_back(s[i]-'0');  // it mean 123 =>[3,2,1]
    }
    return res;
}

void printBigInt(const BigInt& n){  // print value BigInt
    if(n.empty()){
        cout << 0 << endl;
        return;
    }

    for(int i = n.size()-1;i>=0;i--){
        cout << n[i]; // because res have [3,2,1] -> so we need count size to 0 -> [3,2,1] -> 1,2,3
    }

    cout << endl;
}

void removeLeadingZeros(BigInt& num){
    while(num.size()>1 && num.back()==0){
        num.pop_back();
    }
} // remove zero we don't need like [5,6,7,0,0] -> [5,6,7]

BigInt basic_mul(const BigInt& x, const BigInt& y){ // a = [2,1]. b = [4,3]
    if(x.empty()||y.empty()||x.size()==1 && x.back() == 0|| y.size() == 1 && y.back() == 0){
        return {0};
    }

    BigInt res(x.size()+y.size(),0);

    for(size_t i = 0; i<x.size();i++){ 
        int carry = 0;
        for(size_t j = 0; j<y.size(); j++){
            long long current_val = res[i+j] + (long long)x[i]*y[j] + carry; 
            res[i+j] = current_val%10; // 
            carry = current_val/10;
        }
        res[i+y.size()] += carry;
    }
    removeLeadingZeros(res);
    return res;
} 

int main(){
    ifstream infile("ex01_1.inp");
    
    if (!infile.is_open()) {
        cout << "Khong the mo file ex01_1.inp! Hay chac chan ban da tao file nay." << endl;
        return 1;
    }

    string str1, str2;
    infile >> str1 >> str2;
    infile.close();

    BigInt num1 = StingToBigInt(str1);
    BigInt num2 = StingToBigInt(str2);

    BigInt result = basic_mul(num1,num2);

    cout << "So thu nhat: " << str1 << endl;
    cout << "So thu hai : " << str2 << endl;
    cout << "Ket qua nhan : ";
    printBigInt(result);

    return 0;
}