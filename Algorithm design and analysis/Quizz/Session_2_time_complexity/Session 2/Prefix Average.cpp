#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// prefix_averg

void prefix_average1(const vector<int>& a, vector<double>& b) {
    double res = 0.0;
    for(size_t i =0; i<a.size();i++){
        res = a[i];
        for(size_t j = 0; j < i; ++j) {
            res += a[j];
        }
        b[i] = res / (i + 1);
    }
}



void prefix_average2(const vector<int>& a, vector<double>& b) {
    double res = 0.0;
    for(size_t i =0; i<a.size();i++){
        res += a[i];
        b[i] = res / (i + 1);
    }
}

int main() {
    int n = 100000;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        v[i] = i + 1;
    }

    vector<double> res(n); 

    auto start1 = chrono::high_resolution_clock::now();
    prefix_average1(v, res);
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration<double>(end1 - start1).count();
    cout << "Prefix Average 1 Time: " << duration1 << "s" << endl;

    auto start2 = chrono::high_resolution_clock::now();
    prefix_average2(v, res);
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration<double>(end2 - start2).count();
    cout << "Prefix Average 2 Time: " << duration2 << "s" << endl;

    return 0;
}