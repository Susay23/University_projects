// 1 giây =          1,000 ms
// 1 phút =         60,000 ms
// 1 giờ  =      3,600,000 ms
// 1 ngày =     86,400,000 ms

// Với f(n) ms mỗi bước, tìm n lớn nhất có thể giải được trong thời gian t.

// với f(n) = logn, căn n, n, nlogn, n^2, 2^n

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double t = 86400000; // thời gian 1 phút
    double f_n;

    // log n
    f_n = log2(t);
    cout << "log n: " << f_n << endl;

    // căn n
    f_n = sqrt(t);
    cout << "sqrt n: " << f_n << endl;

    // n
    f_n = t;
    cout << "n: " << f_n << endl;

    // n log n
    f_n = t / log2(t);
    cout << "n log n: " << f_n << endl;

    // n^2
    f_n = sqrt(t);
    cout << "n^2: " << f_n << endl;

    // 2^n
    f_n = log2(t);
    cout << "2^n: " << f_n << endl;

    return 0;
}