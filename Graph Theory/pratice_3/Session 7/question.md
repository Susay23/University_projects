Trong một thành phố có N địa điểm được nối với nhau bằng M con đường 1 chiều và 2 chiều. Yêu cầu tối thiểu của một thành phố là từ địa điểm này bạn phải có thể đi đến một địa điểm khác bất kỳ.

Hãy viết chương trình kiểm tra xem các con đường của thành phố có thoả mãn yêu cầu tối thiểu này không. Nếu có in ra OKIE, ngược lại in ra NO.

(nguồn: UVA Online Judge, Problem 11838)

Dữ liệu đầu vào có dạng như sau:

4 5
1 2 1
1 3 2
2 4 1
3 4 1
4 1 2
Trong ví dụ này, có 4 địa điểm và 5 con đường, mỗi con đường có dạng a b p,  trong đó a, b là các địa điểm; và nếu p = 1, con đường đang xét là đường 1 chiều, ngược lại nó là đường 2 chiều.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

- Dòng đầu tiên chứa 2 số nguyên N và M, tương ứng là số địa điểm và số con đường.

- M dòng tiếp theo mỗi dòng chứa 3 số nguyên a, b, p. Nếu p = 1, con đường (a, b) là con đường 1 chiều, ngược lại nếu p = 2, con đường (a, b) là con đường 2 chiều.

Đầu ra (Output):

In ra màn hình OKIE nếu các con đường của thành phố có thoả mãn yêu cầu, ngược lại in ra NO.

Xem thêm ví dụ bên dưới.



Gợi ý:

Xây dựng đồ thị có hướng từ dữ liệu các con đường và các địa điểm
Địa điểm ~ đỉnh
Đường 1 chiều ~ cung
Đường 2 chiều ~ 2 cung
Áp dụng giải thuật kiểm tra đồ thị có liên thông mạnh hay không.
