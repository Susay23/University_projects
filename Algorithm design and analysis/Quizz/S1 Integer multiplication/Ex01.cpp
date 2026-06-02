#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef vector<int> BigInt;

// remove leading zero

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

BigInt mul(const BigInt& x, const BigInt& y){
    BigInt res(x.size()+y.size(),0);
    for(int i = 0;i<x.size();i++){
        int carry = 0;
        for(int j = 0;j<y.size();j++){
            int current_value = res[i+j] + x[i]*y[j] + carry;
            res[i+j] = current_value%10;
            carry = current_value/10;
        }
        res[i+y.size()] = carry;
    }
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
        BigInt result = mul(x,y);
        PrintBigInt(result);
        cout << "-------------------\n";
        cout << endl;
    }
    fclose(f);
    return 0;
}
