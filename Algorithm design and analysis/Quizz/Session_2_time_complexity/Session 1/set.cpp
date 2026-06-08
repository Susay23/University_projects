#include <set>
#include <iostream>
using namespace std;

int main() {
    set<int> s = {3, 1, 2, 1, 3}; 
    
    s.insert(4);       // O(log n) trung bình
    s.erase(2);        // O(log n) trung bình
    
    if (s.count(3))    
        cout << "3 ton tai" << endl; // tìm kiếm O(log n)
    
    for (int x : s)
        cout << x << " "; // in ra theo thứ tự tăng dần 1 2 3 
}
