#include<vector>
#include<string>
#include<iostream>
// Đây là một chương trình C++ để thực hiện phép nhân hai số nguyên lớn (BigInt) được lưu trữ dưới dạng vector<int>
// Chương trình này bao gồm các hàm để chuyển đổi chuỗi số thành BigInt, in BigInt, cộng hai BigInt, nhân một BigInt với 10 mũ power, trừ hai BigInt, và thực hiện phép nhân chia để trị giữa hai BigInt
// Thuật toán nhân chia để trị (divide and conquer) là một thuật toán hiệu quả để nhân hai số lớn, với độ phức tạp thời gian là O(n^log2(3)) ≈ O(n^1.585),
// nhanh hơn so với thuật toán nhân truyền thống có độ phức tạp O(n^2)

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
    return res;
}

void PrintBigInt(const BigInt &num){ 
    // Hàm in ra một số BigInt
    // ví dụ BigInt [3, 2, 1] sẽ được in ra là "123"
    // Chúng ta in các chữ số từ cuối đến đầu của BigInt để hiển thị số theo đúng thứ tự
    for(int i = num.size() - 1; i >= 0; i--){
        cout << num[i];
    }
    cout << endl;
}

BigInt add(const BigInt& x, const BigInt& y){
    // Hàm cộng hai số BigInt
    // Thuật toán này tương tự như cách chúng ta cộng hai số trên giấy, với việc cộng từng chữ số và xử lý phần nhớ
    // ví dụ nếu x = [3, 2, 1] (tương đương với số 123) và y = [6, 5, 4] (tương đương với số 456), thì kết quả sẽ là [9, 7, 5] (tương đương với số 579)
    // Chúng ta cộng từng chữ số của hai BigInt, bắt đầu từ chữ số thấp nhất (chữ số ở vị trí 0) và xử lý phần nhớ nếu tổng vượt quá 9
    BigInt res(max(x.size(), y.size()) + 1, 0);
    int carry = 0;
    for(size_t i = 0; i < res.size(); i++){
        int sum = carry;
        if(i < x.size()) sum += x[i]; // Nếu i nhỏ hơn kích thước của x, chúng ta cộng chữ số tương ứng của x vào tổng
        if(i < y.size()) sum += y[i]; // Nếu i nhỏ hơn kích thước của y, chúng ta cộng chữ số tương ứng của y vào tổng
        res[i] = sum % 10;
        carry = sum / 10;
    }
    if(carry) res.push_back(carry); // Nếu còn phần nhớ sau khi cộng hết tất cả các chữ số, chúng ta thêm phần nhớ đó vào cuối kết quả
    removeleadingzeros(res);
    return res;
}

BigInt mul10power(const BigInt& num, int power){
    // Hàm nhân một số BigInt với 10 mũ power
    // Thuật toán này tương tự như cách chúng ta nhân một số với 10 trên giấy, với việc thêm các số 0 vào cuối số đó
    // ví dụ nếu num = [3, 2, 1] (tương đương với số 123) và power = 2, thì kết quả sẽ là [0, 0, 3, 2, 1] (tương đương với số 12300)
    BigInt res(power, 0);
    res.insert(res.end(), num.begin(), num.end());
    return res;
}

BigInt sub(const BigInt& x, const BigInt& y){
    // Hàm trừ hai số BigInt
    // Thuật toán này tương tự như cách chúng ta trừ hai số trên giấy, với việc trừ từng chữ số và xử lý phần mượn nếu hiệu âm
    // ví dụ nếu x = [3, 2, 1] (tương đương với số 123) và y = [6, 5, 4] (tương đương với số 456), thì kết quả sẽ là [7, 2, 3] (tương đương với số -333)
    // Chúng ta trừ từng chữ số của hai BigInt, bắt đầu từ chữ số thấp nhất (chữ số ở vị trí 0) và xử lý phần mượn nếu hiệu âm
    BigInt res(x.size(), 0); // tạo không gian cho kết quả, kích thước của kết quả sẽ không lớn hơn kích thước của x, nếu bạn tự hỏi tại sao không phải y.size hay là max là vì 
    // chúng ta giả sử x >= y, nếu không thì kết quả sẽ là số âm và chúng ta sẽ không xử lý trường hợp đó trong hàm này
    int borrow = 0;
    for(size_t i = 0; i < x.size(); i++){
        int diff = x[i] - borrow; // Chúng ta bắt đầu với chữ số của x và trừ đi phần mượn từ lần trừ trước đó
        if(i < y.size()) diff -= y[i]; // Nếu i nhỏ hơn kích thước của y, chúng ta trừ chữ số tương ứng của y khỏi diff
        if(diff < 0){ // Nếu diff âm, chúng ta cần mượn 1 từ chữ số tiếp theo của x
            diff += 10; // ví dụ nếu diff = -3, sau khi mượn, diff sẽ trở thành 7 và x là được giảm đi 1 ở chữ số tiếp theo
            borrow = 1;
        } else { // Nếu diff không âm, chúng ta không cần mượn và phần mượn cho lần trừ tiếp theo sẽ là 0
            borrow = 0;
        }
        res[i] = diff; // Chúng ta lưu diff vào kết quả tại vị trí i, ví dụ nếu diff = 7, thì res[i] sẽ là 7
    }
    removeleadingzeros(res); // Xóa các chữ số 0 ở đầu kết quả
    return res;
}

BigInt Karatsuba_mul(const BigInt& x, const BigInt& y){
    // Hàm nhân hai số BigInt bằng cách sử dụng thuật toán nhân chia để trị (divide and conquer)
    // Thuật toán này tương tự như cách chúng ta nhân hai số trên giấy, nhưng chúng ta chia mỗi số thành hai phần và thực hiện phép nhân trên từng phần, sau đó kết hợp kết quả lại với nhau
    if(x.size() == 0 || y.size() == 0 || (x.size() == 1 && x[0] == 0) || (y.size() == 1 && y[0] == 0)){
        return {0};
    }
    
    if(x.size() == 1 && y.size() == 1){
        int mul = (x[0]) * (y[0]); // Nếu cả x và y đều là số có một chữ số, chúng ta có thể nhân trực tiếp hai chữ số đó và trả về kết quả dưới dạng BigInt
        return {mul % 10, mul / 10};
    }

    int n = max(x.size(), y.size()); // Lấy độ dài lớn nhất của hai số để chia chúng thành hai phần
    int half = n / 2; // Chia mỗi số thành hai phần, phần thấp (low) và phần cao (high)

    BigInt x_low(x.begin(), x.begin() + half); // Phần thấp của x bao gồm các chữ số từ vị trí 0 đến half-1
    BigInt x_high(x.begin() + half, x.end()); // Phần cao của x bao gồm các chữ số từ vị trí half đến hết
    BigInt y_low(y.begin(), y.begin() + half); // Phần thấp của y bao gồm các chữ số từ vị trí 0 đến half-1
    BigInt y_high(y.begin() + half, y.end()); // Phần cao của y bao gồm các chữ số từ vị trí half đến hết

    BigInt z0 = Karatsuba_mul(x_low, y_low); // Tính z0 = x_low * y_low
    BigInt z1a = add(x_high, x_low); // Tính z1a = x_high + x_low
    BigInt z1b = add(y_high, y_low); // Tính z1b = y_high + y_low
    BigInt z1_full = Karatsuba_mul(z1a, z1b); // Tính z1_full = (x_high + x_low) * (y_high + y_low)
    BigInt z2 = Karatsuba_mul(x_high, y_high); // Tính z2 = x_high * y_high
    BigInt z1 = sub(sub(z1_full, z2), z0); //  Tính z1 = z1_full - z2 - z0, theo công thức z1 = (x_high + x_low) * (y_high + y_low) - x_high * y_high - x_low * y_low

    BigInt part1 = mul10power(z2, 2 * half);
    BigInt part2 = mul10power(z1, half);
    BigInt result = add(add(part1, part2), z0); // Kết hợp kết quả lại với nhau bằng cách sử dụng công thức: result = (z2 * 10^(2*n/2)) + (z1 * 10^(n/2)) + z0
    removeleadingzeros(result);
    return result;
}

int main(int argc, char* argv[]) {
    if(argc<2){ // Kiểm tra xem người dùng đã cung cấp tên tệp đầu vào hay chưa
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    // Nếu có, mở tệp và đọc hai chuỗi số từ tệp, sau đó chuyển đổi chúng thành BigInt và thực hiện phép nhân
    // Cuối cùng, in ra kết quả của phép nhân
    FILE*input_file = fopen(argv[1], "r");
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
    // Ví dụ nếu str1 = "123" và str2 = "456", thì a sẽ là [3, 2, 1] (tương đương với số 123) và b sẽ là [6, 5, 4] (tương đương với số 456)
    // Chúng ta chuyển đổi chuỗi số thành BigInt bằng cách sử dụng hàm StringToBigInt, sau đó thực hiện phép nhân giữa hai BigInt bằng cách sử dụng hàm Karatsuba_mul,
    // và cuối cùng in ra kết quả của phép nhân
    BigInt a = StringToBigInt(str1);
    BigInt b = StringToBigInt(str2);

    BigInt result = Karatsuba_mul(a, b);
 
    cout << "------------------------------------------" << endl;
    PrintBigInt(a);
    cout << "x ";
    PrintBigInt(b);
    cout << "------------------------------------------" << endl;
    cout << "Ket qua: ";
    PrintBigInt(result);
 
    return 0;
}