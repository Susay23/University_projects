#include<vector>
#include<string>
#include<iostream>
// Đây là một chương trình C++ để thực hiện phép nhân hai số nguyên lớn (BigInt) được lưu trữ dưới dạng vector<int>
// Chương trình này bao gồm các hàm để chuyển đổi chuỗi số thành BigInt

using namespace std;

typedef vector<int> BigInt;

void removeleadingzeros(BigInt &num) { 
    // Hàm loại bỏ các số 0 ở đầu của BigInt
    // ví dụ 000123 sẽ được chuyển thành 123
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

BigInt StringToBigInt(const string& str){ 
    // Hàm chuyển đổi một chuỗi số thành một BigInt
    // Chuỗi số được lưu trữ ngược lại trong BigInt để thuận tiện cho việc tính toán
    // ví dụ chuỗi "123" sẽ được lưu trữ trong BigInt dưới dạng [3, 2, 1]
    BigInt res;
    for(int i = str.size() - 1; i >= 0; i--){
        res.push_back(str[i] - '0');
    } 
    removeleadingzeros(res);
    return res;
}

void PrintBigInt(const BigInt &num){ 
    // Hàm in ra một số BigInt
    // ví dụ BigInt [3, 2, 1] sẽ được in ra là "123"
    for(int i = num.size() - 1; i >= 0; i--){
        cout << num[i];
    }
    cout << endl;
}

BigInt add(const BigInt& x, const BigInt& y){
    // Hàm cộng hai số BigInt
    // Thuật toán này tương tự như cách chúng ta cộng hai số trên giấy, với việc cộng từng chữ số và xử lý phần nhớ
    // ví dụ nếu x = [3, 2, 1] (tương đương với số 123) và y = [6, 5, 4] (tương đương với số 456), thì kết quả sẽ là [9, 7, 5] (tương đương với số 579)
    BigInt res(max(x.size(), y.size()) + 1, 0); // Kết quả có thể có độ dài lớn hơn cả hai số đầu vào, do đó chúng ta tạo một BigInt mới với kích thước lớn hơn nhằm tránh tràn số
    // biến lưu số dư khi cộng
    int carry = 0; 
    for(size_t i = 0; i < res.size(); i++){
        // tổng của hai chữ số tương ứng của x và y cùng với phần nhớ carry
        int sum = carry;
        if(i < x.size()) sum += x[i]; // nếu i nhỏ hơn kích thước của x, chúng ta cộng chữ số tương ứng của x vào tổng ví dụ i = 0, chúng ta cộng x[0] vào tổng, i = 1 chúng ta cộng x[1] vào tổng, v.v.
        if(i < y.size()) sum += y[i]; // nếu i nhỏ hơn kích thước của y, chúng ta cộng chữ số tương ứng của y vào tổng ví dụ i = 0, chúng ta cộng y[0] vào tổng, i = 1 chúng ta cộng y[1] vào tổng, v.v.
        res[i] = sum % 10; // chữ số cuối cùng của tổng sẽ được lưu trữ trong kết quả ví dụ nếu sum = 15, thì res[i] sẽ là 5
        carry = sum / 10; // phần còn lại của tổng sẽ được lưu trữ trong biến carry để cộng vào chữ số tiếp theo ví dụ nếu sum = 15, thì carry sẽ là 1 và sẽ được cộng vào chữ số tiếp theo
    }
    removeleadingzeros(res); // xóa số 0 ở đầu của kết quả ví dụ nếu res = [0, 5, 7, 9], thì sau khi loại bỏ số 0 ở đầu, res sẽ trở thành [5, 7, 9]
    return res;
}

BigInt mul10power(const BigInt& num, int power){
    // Hàm nhân một số BigInt với 10 mũ power
    // Thuật toán này tương tự như cách chúng ta nhân một số với 10 trên giấy, với việc thêm các số 0 vào cuối số đó
    // ví dụ nếu num = [3, 2, 1] (tương đương với số 123) và power = 2, thì kết quả sẽ là [0, 0, 3, 2, 1] (tương đương với số 12300)
    BigInt res(power, 0); // nghĩa là chúng ta tạo một BigInt mới với power số 0 ở đầu để nhân với 10 mũ power ví dụ nếu power = 2, thì res sẽ là [0, 0]
    res.insert(res.end(), num.begin(), num.end()); // sau đó chúng ta chèn các chữ số vào theo thứ tự res.end, num.begin, num.end ví dụ nếu num = [3, 2, 1] và res = [0, 0], thì sau khi chèn, res sẽ trở thành [0, 0, 3, 2, 1]
    return res;
}

BigInt DivideAndConquer_mul(const BigInt& x, const BigInt& y){
    // Hàm nhân hai số BigInt bằng cách sử dụng thuật toán nhân chia để trị (divide and conquer)
    // Thuật toán này tương tự như cách chúng ta nhân hai số trên giấy, nhưng
    // chúng ta chia mỗi số thành hai phần và thực hiện phép nhân trên từng phần, sau đó kết hợp kết quả lại với nhau
    // ví dụ nếu x = [3, 2, 1] (tương đương với số 123) và y = [6, 5, 4] (tương đương với số 456), thì kết quả sẽ là [8, 8, 0, 5] (tương đương với số 56088)
    // nếu a hoặc b bằng 0 hoặc a hoặc b có 1 chữ số và giá trị là 0 thì kết quả là 0
    if(x.size() == 0 || y.size() == 0 || (x.size() == 1 && x[0] == 0) || (y.size() == 1 && y[0] == 0)){
        return {0};
    }
    // nếu a và b có 1 chữ số thì kết quả là tích của 2 chữ số đó
    if(x.size() == 1 && y.size() == 1){
        int mul = (x[0]) * (y[0]);
        return {mul % 10, mul / 10};
    }


    // (z2)*(10^2*half) + (z1a + z1b)*(10^half) + z0

    int n = max(x.size(), y.size()); // Lấy độ dài lớn nhất của hai số để chia chúng thành hai phần
    int half = n / 2; // Chia mỗi số thành hai phần, phần thấp (low) và phần cao (high)
    
    // Ví dụ nếu n = 5, thì half sẽ là 2, và chúng ta sẽ chia số thành phần thấp gồm 2 chữ số cuối và phần cao gồm các chữ số còn lại
    // Chia x và y thành phần thấp và phần cao
    // chia a và b thành 2 phần: phần cao và phần thấp
    BigInt x_low(x.begin(), x.begin() + half); // x thấp tình từ điểm x[0] đến x[half-1] ví dụ nếu x = [3, 2, 1] và half = 2, thì x_low sẽ là [2, 1]
    BigInt x_high(x.begin() + half, x.end()); // x cao tình từ điểm x[half] đến x[n-1] ví dụ nếu x = [3, 2, 1] và half = 2, thì x_high sẽ là [3]
    BigInt y_low(y.begin(), y.begin() + half); // tương tự với y ví dụ nếu y = [6, 5, 4] và half = 2, thì y_low sẽ là [5, 4]
    BigInt y_high(y.begin() + half, y.end()); //  y_high sẽ là [6]

    // Thực hiện phép nhân chia để trị
    // Chúng ta sẽ tính z0 = x_low * y_low, z1 = (x_low * y_high) + (x_high * y_low), và z2 = x_high * y_high
    // Sau đó, kết hợp kết quả lại với nhau bằng cách sử dụng công thức:
    BigInt z0 = DivideAndConquer_mul(x_low, y_low); // z0 = x_low * y_low
    BigInt z1a = DivideAndConquer_mul(x_low, y_high); // z1a = x_low * y_high
    BigInt z1b = DivideAndConquer_mul(x_high, y_low); // z1b = x_high * y_low
    BigInt z2 = DivideAndConquer_mul(x_high, y_high); // z2 = x_high * y_high
    BigInt z1 = add(z1a, z1b); // z1 = (x_low * y_high) + (x_high * y_low)

    BigInt part1 = mul10power(z2, 2 * half); // part1 = z2 * 10^(2*n/2)
    BigInt part2 = mul10power(z1, half); // part2 = z1 * 10^(n/2)
    BigInt result = add(add(part1, part2), z0); // result = (z2 * 10^(2*n/2)) + (z1 * 10^(n/2)) + z0
    removeleadingzeros(result); // Loại bỏ các số 0 ở đầu của kết quả
    return result; // Trả về kết quả của phép nhân hai số BigInt
}

int main(int argc, char* argv[]) {
    // Kiểm tra xem người dùng đã cung cấp tên tệp đầu vào hay chưa
    // Nếu không, in ra hướng dẫn sử dụng và thoát chương trình
    // Nếu có, mở tệp và đọc hai chuỗi số từ tệp, sau đó chuyển đổi chúng thành BigInt và thực hiện phép nhân
    // Cuối cùng, in ra kết quả của phép nhân
    if(argc<2){
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    FILE*input_file = fopen(argv[1], "r");
    if (!input_file) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    char buffer1[10000];
    char buffer2[10000];
    fscanf(input_file, "%s %s", buffer1, buffer2);
    fclose(input_file);
    string str1 = buffer1, str2 = buffer2;
    
    // Đọc hai chuỗi số từ tệp đầu vào và lưu chúng vào buffer1 và buffer2
    // Sau đó, đóng tệp và chuyển đổi các chuỗi này thành BigInt để thực hiện phép nhân
    // Ví dụ nếu str1 = "123" và str2 = "456", thì a sẽ là [3, 2, 1] (tương đương với số 123) và b sẽ là [6, 5, 4] (tương đương với số 456)

    BigInt a = StringToBigInt(str1);
    BigInt b = StringToBigInt(str2);

    BigInt result = DivideAndConquer_mul(a, b);
 
    cout << "------------------------------------------" << endl;
    PrintBigInt(a);
    cout << "x ";
    PrintBigInt(b);
    cout << "------------------------------------------" << endl;
    cout << "Ket qua: ";
    PrintBigInt(result);
    // bonus nếu muốn in nhiều cặp thì sửa thành thế này
    // char buf1[10000], buf2[10000];
    // int pair = 1;
    // while (fscanf(f, "%s %s", buf1, buf2) == 2) {
    //     BigInt a = StringtoBigInt(string(buf1));
    //     BigInt b = StringtoBigInt(string(buf2));
    //     BigInt res = DAC_mul(a, b);

    //     cout << "--- Cap " << pair++ << " ---" << endl;
    //     printBigInt(a);
    //     cout << "x ";
    //     printBigInt(b);
    //     cout << "= ";
    //     printBigInt(res);
    //     cout << endl;
    // }
    return 0;
}