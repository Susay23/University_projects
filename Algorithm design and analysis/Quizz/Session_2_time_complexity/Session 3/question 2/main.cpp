//Tìm n nhỏ nhất để 100n² nhanh hơn 2^n (trên cùng máy tính)

#include <iostream>
#include <cmath>
using namespace std;

// 100n^2 < 2^n

int main(){
    // tìm số nguyên n nhỏ nhất để 100n² < 2^n nghĩ là tạo vòng lặp while tăng n đến khi nào 100n² >= 2^n thì dừng lại, lúc đó n chính là giá trị nhỏ nhất
    int n = 1;
    while (100 * n * n >= pow(2, n)) {
        n++;
    }
    cout << "Value of n: " << n << endl;
    return 0;
}