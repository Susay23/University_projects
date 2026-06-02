#include <map>
#include <iostream>
using namespace std;

int main() {
    map<string, int> diemSV;
    
    diemSV["An"] = 8;
    diemSV["Binh"] = 9;
    diemSV["An"] = 10;  // ghi đè — key không trùng
    
    // tìm kiếm
    if (diemSV.count("An"))
        cout << "Diem An: " << diemSV["An"] << endl;
    
    for (auto& [key, val] : diemSV)
        cout << key << ": " << val << endl;
    // in ra theo thứ tự alphabet
}
