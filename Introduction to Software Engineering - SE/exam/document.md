# PHẦN I: TỔNG QUAN VỀ CÔNG NGHỆ PHẦN MỀM
## 1. Phần mềm (Software)
Bao gồm các chương trình máy tính, tài liệu liên quan (phân tích yêu cầu, đặc tả, thiết kế, kiểm thử) và các thủ tục vận hành dùng để thiết lập, điều hành hệ thống phần mềm
## 2. Công nghệ phần mềm (Software Engineering)
Là việc áp dụng một cách tiếp cận có hệ thống, bài bản và có thể thượng lượng hoá được vào quá trình phát triển, vận hành và bảo trì phần mềm -- nói cách khác là áp dụng các nguyên tắc kỹ thuật (Engineẻing) vào phần mềm.
## 3. Phân biệt: Sai sót – Khiếm khuyết – Sự cố
Theo chuẩn IEEE đã phân biệt rõ 3 khái niệm dễ gây nhầm lẫn theo chuỗi nhân quả: con người gây sai sót -> sai sót tạo ra khiếm khuyết nằm tĩnh trong sản phẩm -> khiếm khuyết kích hoạt lúc chạy sinh ra sự cố.
| Thuật Ngữ | Nguyên Nhân Gốc & Định Nghĩa | Tầm Nhìn & Mối Quan Hệ |
| --------- | ---------------------------- | ---------------------- |
|Error (sai sót)|hành động của con người trong lúc phát triển tạo ra kết quả sai (do giới hạn nhận thức hoặc hiểu sai đặc tả)|Thường chỉ tồn tại trong nhận thức người tạo ra nó. Sai sót là nguyên nhân đưa khiếm khuyết vào sản phẩm|
|Defect/fault (khiếm khuyết/lỗi tĩnh)|Một khiếm khuyết trong sản phẩm phần mềm (đặc tả,thiết kế,mã nguồn,tài liệu) do sai sót của con người đưa vào|Tồn tại tĩnh bên trong sản phẩm.Khi gặp dữ liệu/điều kiện cụ thể lúc chạy, khiếm khuyết này kích hoạt thành sự cố|
|Failure (sự cố)|Sự sai lệch có thể quan sát được của hệ thống so với hành vi mong đợi được thực thi thực tế|Người dùng/kiểm thử viên quan sát được. Là kết quả trực tiếp của việc kích hoạt khiếm khuyết|
## 4. Phân bổ công sức phát triển phần mềm
> Công thức 40 - 20 - 40 và tỷ lệ chi tiết
> + Bảo trì chiếm 50 - 70% tổng chi phí vòng đời phần mềm
> + Quy tắc 40 - 20 -40: 40% Phân tích/ Thiết kế - 20% Lập Trình - 40% Kiểm thử
> + Chi tiết: Xác định yêu cầu 10% - Đặc tả 10% - Thiết kế 15 - Cài đặt 20% - kiểm thử 45%
# PHẦN II: CÁC MÔ HÌNH QUY TRÌNH PHẦN MỀM (SDLC)
## 1. Mô hình Thác nước (Waterfall Model)
Mô hình tuần tự tuyến tính: mỗi giai đoạn phải hoàn thành và lập tài liệu đầy đủ trước khi giai đoạn sau bắt đầu. Ưu điểm: cấu trúc rõ ràng, dễ giải thích. Nhược điểm: yêu cầu bị đóng băng cứng nhắc, người dùng phải chờ rất lâu mới thấy sản phẩm chạy được.
## 2. Mô hình chữ V (V-Model)
Biến thể của Waterfall, ánh xạ mỗi giai đoạn phát triển (bên trái) với một giai đoạn kiểm chứng/kiểm thử tương ứng (bên phải). Ánh xạ cốt lõi: 
+ Kiểm thử đơn vị (Unit Testing) kiểm chứng Thiết kế chương trình
+ Kiểm thử tích hợp (Integration Testing) kiểm chứng Thiết kế hệ thống
+ Kiểm thử chấp nhận (Acceptance Testing) xác thực Yêu cầu
## 3. Mô hình lập bản mẫu (Prototyping Model)
Xây dựng một bản chưa hoàn chỉnh (prototype) để làm rõ yêu cầu và giảm rủi ro. Gồm hai loại:
+ Throwaway prototype (bản mẫu bỏ đi) — chỉ dùng để thăm dò rồi bỏ.
+ Evolutionary prototype (bản mẫu tiến hoá) — được tinh chỉnh liên tục để trở thành hệ thống cuối cùng.
## 4. Tăng trưởng (Incremental) so với Lặp (Iterative)
+ Incremental: bắt đầu với lõi chức năng nhỏ, mỗi lần phát hành bổ sung thêm phần tăng trưởng.
+ Iterative: bắt đầu với hệ thống đầy đủ nhưng ở mức sơ khai, sau đó liên tục tinh chỉnh từng phân hệ qua mỗi phiên bản.
## 5. Mô hình Xoắn ốc (Spiral Model)
Mô hình lặp do Barry Boehm đề xuất, kết hợp hoạt động kỹ thuật với Risk Management (Quản lý rủi ro) nghiêm ngặt. Di chuyển qua 4 phần tư: 1) Lập kế hoạch → 2) Xác định mục tiêu/giải pháp/ràng buộc → 3) Đánh giá giải pháp và rủi ro → 4) Phát triển và kiểm thử.
## 6. Agile & Scrum
Agile đề cao con người, phần mềm chạy tốt, hợp tác và phản hồi thay đổi. Scrum là khung Agile phổ biến dựa trên 3 trụ cột: Minh bạch (Transparency), Kiểm tra (Inspection), Thích nghi (Adaptation).
|Thành phần Scrum|Chi tiết|
|---|---|
|3 Vai trò|Product Owner (quản lý Product Backlog) — Scrum Master (quản lý quy trình, gỡ trở ngại) — Developers (tự quản lý, tạo ra Increment)|
|5 Sự kiện|Sprint (≤1 tháng) — Sprint Planning (≤8h) — Daily Scrum (≤15p) — Sprint Review (≤4h) — Sprint Retrospective (≤3h)|
|3 Sản phẩm|Product Backlog — Sprint Backlog — Incremen|
## 7. RUP (Rational Unified Process):
+ Trục động (Phases): Inception (xác định phạm vi) → Elaboration (nền tảng kiến trúc, giảm rủi ro) → Construction (phát triển thành phần) → Transition (chuyển giao).
+ Trục tĩnh (Disciplines): 9 luồng công việc — Business Modeling, Requirements, Analysis & Design, Implementation, Test, Deployment, Configuration Management, Project Management, Environment.
# PHẦN III: PHÂN TÍCH, ĐẶC TẢ & MÔ HÌNH HÓA YÊU CẦU
## 1. Functional vs Non-Functional Requirements:
+ Functional: hệ thống làm gì.
+ Non-Functional: hệ thống làm tốt đến mức nào (hiệu suất, độ tin cậy, bảo mật, usability...).
## 2. Validation vs Verification:
+ Validation (Xác thực): "Chúng ta có đang xây đúng sản phẩm không?" — đánh giá cuối quy trình, so với nhu cầu khách hàng.
+ Verification (Kiểm chứng): "Chúng ta có đang xây sản phẩm đúng cách không?" — đánh giá sản phẩm của từng giai đoạn so với điều kiện đầu vào giai đoạn đó.
> Note: mẹo nhớ tiếng Anh — Validation = "right product", Verification = "product right".
### Các ký hiệu mô hình hóa yêu cầu:
+ ERD (Entity-Relationship Diagram): Entities – Relationships – Attributes.
+ UML Class Diagram: lớp, thuộc tính, phương thức, quan hệ (aggregation, composition).
+ Sequence Diagram (Event Trace): timeline trao đổi message giữa các thực thể.
+ State Machine / Statechart: trạng thái ổn định + transition kích hoạt bởi event.
+ DFD (Data-Flow Diagram) / Use Case Diagram: actor, boundary, use case, quan hệ (include, extend).
## 3. Công thức đo lường chất lượng yêu cầu
1. Specificity — Độ cô đọng (tránh mơ hồ): Q₁ = n_ui / n_r (n_ui = số yêu cầu được mọi reviewer hiểu giống nhau; n_r = tổng yêu cầu = n_f + n_nf)
2. Completeness — Độ hoàn chỉnh: Q₂ = n_u / (n_i × n_s) (n_u = số yêu cầu chức năng duy nhất; n_i = số input; n_s = số state)
3. Validation Degree — Độ hợp lệ: Q₃ = n_c / (n_c + n_nv) (n_c = yêu cầu đã xác thực đúng; n_nv = yêu cầu chưa xác thực)
> Note: cả 3 công thức đều dạng "tỉ lệ phần đạt / tổng thể" — chỉ cần nhớ tử số/mẫu số là gì.
# PHẦN IV: THIẾT KẾ & KIẾN TRÚC PHẦN MỀM
4 mức thiết kế:
+ Architectural Design — phân rã hệ thống thành khối chức năng lớn, chọn tech stack.
+ Data Design — cấu trúc dữ liệu, schema DB, ràng buộc toàn vẹn.
+ Interface Design — API hệ thống-hệ thống, UI/UX người dùng-hệ thống.
+ Detailed Design — lớp, thuộc tính, phương thức, thuật toán cụ thể.