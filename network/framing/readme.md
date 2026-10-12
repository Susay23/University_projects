Bước 0: Hiểu bài toán

Bên gửi cắt file thành nhiều đoạn, mỗi đoạn dài tối đa len byte. Mỗi đoạn được bọc thành một khung. Bên nhận cần biết chỗ nào khung bắt đầu và kết thúc, nên ta thêm cờ hiệu (flag) ở đầu và cuối khung.

Vấn đề là dữ liệu trong file có thể tình cờ chứa đúng byte giống cờ hiệu, và bên nhận sẽ tưởng khung đã kết thúc. Cách xử lý gọi là stuffing (chèn thêm). Đề bài yêu cầu hai phương pháp.

Bước 1: Đọc file dạng nhị phân
cpp
FILE* f = fopen(filename, "rb");

Phải dùng "rb", không dùng "r". Chế độ văn bản có thể làm hỏng một số byte (ví dụ trên Windows). Đọc cả file vào vector<byte>, với byte là unsigned char để giá trị từ 0 đến 255.

Bước 2: Byte stuffing (cờ hiệu + ESC)

Cấu trúc khung: FLAG | dữ liệu | FLAG.

Quy tắc: nếu byte dữ liệu trùng flag hoặc esc, chèn thêm một byte esc ngay trước nó.

cpp
if (p[i] == flag || p[i] == esc) frame.push_back(esc);
frame.push_back(p[i]);

Phải chèn ESC trước cả byte trùng ESC, nếu không bên nhận sẽ nhầm byte ESC thật của dữ liệu với dấu hiệu “byte tiếp theo là dữ liệu”.

Kết quả chạy thử với file AB~CD... và len=5, dùng FLAG=0x7E, ESC=0x7D:

Khung 1: 7E 41 42 7D 7E 43 7D 7D 7E

Đọc khung này: 7E là cờ mở, 41 42 là chữ A và B, 7D 7E là ESC rồi 7E (dữ liệu thật là ~), 43 là chữ C, 7D 7D là ESC rồi 7D (dữ liệu thật là }), 7E cuối là cờ đóng. Khung tạo ra 9 byte từ 5 byte dữ liệu.

Bước 3: Hàm đúng chữ ký đề bài
cpp
int framing(char* filename, int len, byte flag, byte esc)

Hàm này cắt file thành từng đoạn len byte (đoạn cuối có thể ngắn hơn), gọi hàm chèn ESC cho mỗi đoạn, in khung ra màn hình dạng hex, và trả về số khung. Hàm trả -1 nếu lỗi, ví dụ không mở được file, len <= 0, hoặc flag == esc. Hai giá trị này bắt buộc phải khác nhau, nếu trùng thì bên nhận không phân biệt được.

Bước 4: Phía nhận (để tự kiểm tra)

Mình thêm hàm byteUnstuff để chứng minh phương pháp đúng. Nó quét từng byte và xử lý ba trường hợp:

Gặp flag khi ngoài khung thì bắt đầu khung.
Gặp esc trong khung thì bỏ ESC và lấy luôn byte sau nó làm dữ liệu thật.
Gặp flag khi trong khung thì kết thúc khung.

Chương trình ghép dữ liệu tách được và so với file gốc. Dòng Kiem tra tach khung: DUNG nghĩa là khớp từng byte.

Bước 5: Bit stuffing (cờ bắt đầu/kết thúc)

Cờ là mẫu bit 01111110 (6 bit 1 liên tiếp ở giữa). Đây là cách của HDLC.

Quy tắc: trong dữ liệu, cứ gặp 5 bit 1 liên tiếp thì chèn ngay một bit 0. Nhờ vậy dữ liệu không bao giờ chứa 6 bit 1 liên tiếp, nên không thể giống cờ.

cpp
if (bit) { if (++ones == 5) { bits += '0'; ones = 0; } }
else ones = 0;

Biến ones đếm số bit 1 liên tiếp. Bit 0 làm đếm về 0. Duyệt bit từ cao đến thấp trong mỗi byte (k = 7 xuống 0). Phía nhận làm ngược lại: gặp 5 bit 1 thì bỏ bit đứng sau nó.

Bước 6: Biên dịch và chạy
bash
g++ -std=c++11 -o framing framing.cpp
./framing duongdan_file 5

Đối số thứ hai là len. Bạn thử các file khác nhau: một file toàn chữ, một file có byte 0x7E và 0x7D, và file có byte 0xFF (8 bit 1, sẽ kích hoạt bit stuffing).