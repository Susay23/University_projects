Viết chương trình tìm cây khung có trọng số nhỏ nhất bằng giải thuật Kruskal.

Đầu vào:

Dữ liệu đầu vào được nhập từ bàn phím với định dạng

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 3 số nguyên u, v, w mô tả cung (u, v) có trọng số w.

Đầu ra:

In ra màn hình trọng số của cây khung tìm được và danh sách các cung theo thứ tự tăng dần của trọng số.

Quy ước: các cung được in ra theo định dạng:

u v w

với (u < v), mỗi cung trên 1 dòng. Nếu hai cung có trọng số bằng nhau thì cung nào có u nhỏ hơn sẽ được in trước. Nếu có trọng số bằng nhau và u giống nhau thì cung nào có v nhỏ hơn sẽ in trước.

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
