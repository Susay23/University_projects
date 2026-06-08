#include <unordered_set>
#include <iostream>
using namespace std;

int main() {
    unordered_set<int> us = {3, 1, 2, 1, 3};
    
    us.insert(5);      // O(1) trung bình
    us.erase(2);       // O(1) trung bình
    
    if (us.count(3))
        cout << "3 ton tai" << endl;
    
    for (int x : us)
        cout << x << " "; // thứ tự KHÔNG đảm bảo
}
