#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};
    
    v.push_back(4);       // thêm cuối
    v.pop_back();         // xóa cuối
    v.insert(v.begin(), 0); // chèn đầu — O(n)
    
    cout << v[1] << endl; // truy cập theo index — O(1)
    
    for (int x : v)
        cout << x << " ";
}
