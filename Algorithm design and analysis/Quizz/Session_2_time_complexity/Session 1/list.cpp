#include <list>
#include <iostream>
using namespace std;

int main() {
    list<int> l = {1, 2, 3};
    
    l.push_front(0);   // thêm đầu — O(1)
    l.push_back(4);    // thêm cuối — O(1)
    l.pop_front();     // xóa đầu — O(1)
    
    // KHÔNG có truy cập l[i] — phải duyệt qua danh sách để tìm phần tử thứ i, O(n)
    for (int x : l)
        cout << x << " ";
}
