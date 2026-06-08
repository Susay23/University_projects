#include<vector>
#include<string>
#include<iostream>
// Đây là một chương trình C++ để thực hiện phép nhân hai số nguyên lớn (BigInt) được lưu trữ dưới dạng vector<int>
// Chương trình này bao gồm các hàm để chuyển đổi chuỗi số thành BigInt, in BigInt, và thực hiện phép nhân cơ bản giữa hai BigInt

using namespace std;

typedef vector<int> BigInt;

void removeleadingzeros(BigInt &num) { 
    while (num.size() > 1 && num.back() == 0) { // nếu số có nhiều hơn một chữ số và chữ số cuối cùng là 0, chúng ta sẽ loại bỏ nó
        // Hàm loại bỏ các số 0 ở đầu của BigInt
        // ví dụ 000123 sẽ được chuyển thành 123
        num.pop_back(); // pop_back có nghĩa là loại bỏ phần tử cuối cùng của vector, ở đây chúng ta loại bỏ chữ số 0 cuối cùng
    }
}

BigInt StringToBigInt(const string& str){ 
    // Hàm chuyển đổi một chuỗi số thành một BigInt
    BigInt res;
    for(int i = str.size() - 1; i >= 0; i--){ // với i là kích thước của chuỗi trừ đi 1 (vì chỉ số bắt đầu từ 0), chúng ta sẽ duyệt ngược chuỗi để chuyển đổi từng ký tự thành số nguyên và lưu vào BigInt
        // Chuỗi số được lưu trữ ngược lại trong BigInt để thuận tiện cho việc tính toán
        // ví dụ chuỗi "123" sẽ được lưu trữ trong BigInt dưới dạng [3, 2, 1]
        res.push_back(str[i] - '0'); // push_back có nghĩa là thêm phần tử vào cuối vector, ở đây chúng ta thêm chữ số đã được chuyển đổi từ ký tự sang số nguyên
    } 
    return res;
}

void PrintBigInt(const BigInt &num){ 
    // Hàm in ra một số BigInt
    // ví dụ BigInt [3, 2, 1] sẽ được in ra là "123"
    for(int i = num.size() - 1; i >= 0; i--){ 
        cout << num[i]; 
    }
    cout << endl; // sau khi in xong số, chúng ta sẽ in một dòng mới để kết thúc
} 

BigInt Basic_mul(const BigInt& x, const BigInt& y){
    // Hàm nhân hai số BigInt bằng cách sử dụng thuật toán nhân truyền thống
    // Thuật toán này tương tự như cách chúng ta nhân hai số trên giấy, với việc nhân từng chữ số và cộng dồn kết quả
    // ví dụ nếu x = [3, 2, 1] (tương đương với số 123) và y = [6, 5, 4] (tương đương với số 456), thì kết quả sẽ là [8, 8, 0, 5] (tương đương với số 56088)
    BigInt res(x.size() + y.size(),0);
    for(int i = 0; i< x.size();i++){
        int carry = 0;
        for(int j=0; j<y.size();j++){
            int current_val = res[i+j] + x[i] * y[j] + carry;
            res[i+j] = current_val % 10;
            carry = current_val / 10;
        }
        // Sau khi nhân x[i] với tất cả các chữ số của y, chúng ta cần cộng thêm carry vào phần tiếp theo của kết quả
        res[i + y.size()] += carry; 
    }
    removeleadingzeros(res);
    return res;
}

int main(int argc, char* argv[]) {
    // Kiểm tra xem người dùng đã cung cấp tên tệp đầu vào hay chưa
    // Nếu không, in ra hướng dẫn sử dụng và thoát chương trình
    // Nếu có, mở tệp và đọc hai chuỗi số từ tệp, sau đó chuyển đổi chúng thành BigInt và thực hiện phép nhân
    // Cuối cùng, in ra kết quả của phép nhân
    if(argc<2){ // argc là số lượng đối số được truyền vào chương trình, nếu nhỏ hơn 2 nghĩa là người dùng chưa cung cấp tên tệp đầu vào
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    // nếu muốn chạy nhiều số hơn thì có thể sửa lại code để đọc nhiều hơn 2 chuỗi số từ tệp và thực hiện phép nhân cho tất cả các cặp số đó ví dụ
    // for(int i = 1; i < argc; i+=2){
    //     char buffer1[10000];
    //     char buffer2[10000];
    //     fscanf(input_file, "%s %s", buffer1, buffer2);
    //     BigInt a = StringToBigInt(buffer1);
    //     BigInt b = StringToBigInt(buffer2);
    //     BigInt result = Basic_mul(a, b);
    // }
    FILE*input_file = fopen(argv[1], "r"); // mở tệp đầu vào để đọc, nếu tệp không tồn tại hoặc không thể mở được, in ra lỗi và thoát chương trình
    if (!input_file) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }
    // Đọc hai chuỗi số từ tệp đầu vào và lưu chúng vào buffer1 và buffer2
    // Sau đó, đóng tệp và chuyển đổi các chuỗi này thành BigInt để thực hiện phép nhân
    char buffer1[10000];
    char buffer2[10000];
    fscanf(input_file, "%s %s", buffer1, buffer2);
    fclose(input_file);
    string str1 = buffer1, str2 = buffer2;
    
    BigInt a = StringToBigInt(str1);
    BigInt b = StringToBigInt(str2);

    BigInt result = Basic_mul(a, b);
 
    cout << "------------------------------------------" << endl;
    PrintBigInt(a);
    cout << "x ";
    PrintBigInt(b);
    cout << "------------------------------------------" << endl;
    cout << "Ket qua: ";
    PrintBigInt(result);

    return 0;
}