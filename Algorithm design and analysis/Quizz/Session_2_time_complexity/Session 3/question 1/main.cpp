// Giải thuật 1: 8n² bước — Giải thuật 2: 64n log n bước. Tìm n để GT1 tốt hơn GT2?

#include <iostream>
#include <cmath>
using namespace std;

// 8n² < 64n log n
// n < 8 log n
// n/log n < 8 với bậc của log là 2

int main(){
    int n = 2;
    while (n / log2(n) < 8) {
        n++;
    }
    cout << "Value of n: " << n << endl;
    return 0;
}