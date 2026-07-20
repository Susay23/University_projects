Cho đồ thị có hướng G = <V, E> có n đỉnh và m cung (n < 100, m < 500). Mỗi cung được gán một trọng số w (-100 < w <= 100).

Áp dụng giải thuật Floyd - Warshall viết chương trình tìm đường đi ngắn nhất giữa các cặp đỉnh. In chiều dài ngắn nhất giữa các cặp đỉnh ra màn hình theo dạng:

x -> y: chiều dài

...



Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

Dòng đầu tiên chứa 2 số nguyên n và m.
m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.
Dữ liệu được đảm bảo không tồn tại chu trình âm.

Đầu ra (Output):

In ra màn hình chiều dài đường đi ngắn nhất giữa các cặp đỉnh. Nếu không có đường đi in ra oo (vô cùng).

Liệt kê các cặp theo thứ tự tăng dần của x, và y.

Xem thêm ví dụ bên dưới.

Chú ý:

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &c);
		add_edge(&G, u, v, w);
	}