#include <unordered_map>
#include <iostream>
using namespace std;

int main() {
    unordered_map<string, int> diemSV;
    
    diemSV["An"] = 8;
    diemSV["Binh"] = 9;
    
    // tìm kiếm O(1) trung bình
    if (diemSV.count("An"))
        cout << "Diem An: " << diemSV["An"] << endl;
    
    for (auto& [key, val] : diemSV)
        cout << key << ": " << val << endl;
    // thứ tự KHÔNG đảm bảo
}
