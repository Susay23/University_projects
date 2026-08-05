# PHẦN I: TỔNG QUAN VỀ CÔNG NGHỆ PHẦN MỀM
## 1. Phần mềm (Software)
Bao gồm các chương trình máy tính, tài liệu liên quan (phân tích yêu cầu, đặc tả, thiết kế, kiểm thử) và các thủ tục vận hành dùng để thiết lập, điều hành hệ thống phần mềm
## 2. Công nghệ phần mềm (Software Engineering)
Là việc áp dụng một cách tiếp cận có hệ thống, bài bản và có thể thượng lượng hoá được vào quá trình phát triển, vận hành và bảo trì phần mềm -- nói cách khác là áp dụng các nguyên tắc kỹ thuật (Engineẻing) vào phần mềm.
## 3. Phân biệt: Sai sót – Khiếm khuyết – Sự cố
Theo chuẩn IEEE đã phân biệt rõ 3 khái niệm dễ gây nhầm lẫn theo chuỗi nhân quả: con người gây sai sót -> sai sót tạo ra khiếm khuyết nằm tĩnh trong sản phẩm -> khiếm khuyết kích hoạt lúc chạy sinh ra sự cố.
| Thuật Ngữ                            | Nguyên Nhân Gốc & Định Nghĩa                                                                                  | Tầm Nhìn & Mối Quan Hệ                                                                                            |
| ------------------------------------ | ------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| Error (sai sót)                      | hành động của con người trong lúc phát triển tạo ra kết quả sai (do giới hạn nhận thức hoặc hiểu sai đặc tả)  | Thường chỉ tồn tại trong nhận thức người tạo ra nó. Sai sót là nguyên nhân đưa khiếm khuyết vào sản phẩm          |
| Defect/fault (khiếm khuyết/lỗi tĩnh) | Một khiếm khuyết trong sản phẩm phần mềm (đặc tả,thiết kế,mã nguồn,tài liệu) do sai sót của con người đưa vào | Tồn tại tĩnh bên trong sản phẩm.Khi gặp dữ liệu/điều kiện cụ thể lúc chạy, khiếm khuyết này kích hoạt thành sự cố |
| Failure (sự cố)                      | Sự sai lệch có thể quan sát được của hệ thống so với hành vi mong đợi được thực thi thực tế                   | Người dùng/kiểm thử viên quan sát được. Là kết quả trực tiếp của việc kích hoạt khiếm khuyết                      |
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
| Thành phần Scrum | Chi tiết                                                                                                                            |
| ---------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| 3 Vai trò        | Product Owner (quản lý Product Backlog) — Scrum Master (quản lý quy trình, gỡ trở ngại) — Developers (tự quản lý, tạo ra Increment) |
| 5 Sự kiện        | Sprint (≤1 tháng) — Sprint Planning (≤8h) — Daily Scrum (≤15p) — Sprint Review (≤4h) — Sprint Retrospective (≤3h)                   |
| 3 Sản phẩm       | Product Backlog — Sprint Backlog — Incremen                                                                                         |
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
### Coupling (Ghép nối mô-đun) — mục tiêu: thấp/lỏng
Từ tệ nhất đến tốt nhất:

| Mức        | Coupling                 | Mô tả ngắn                                                                                   |
| ---------- | ------------------------ | -------------------------------------------------------------------------------------------- |
| Tệ nhất    | Content (nội dung)       | Module này sửa/truy cập trực tiếp dữ liệu nội bộ module kia, hoặc nhảy giữa code module khác |
| Tight      | Common (chung)           | Nhiều module cùng dùng chung vùng biến toàn cục                                              |
| Trung bình | Control (điều khiển)     | Truyền tham số/cờ để điều khiển luồng logic module kia                                       |
| Lỏng       | Stamp (tham số cấu trúc) | Truyền cả object/record dù chỉ dùng vài field                                                |
| Tốt nhất   | Data (dữ liệu)           | Chỉ truyền giá trị đơn giản, giao diện sạch nhất                                             |

> Note: học theo thứ tự Content → Common → Control → Stamp → Data (tệ → tốt), viết tắt dễ nhớ: "C-C-C-S-D".

### Cohesion (Sự gắn kết) — mục tiêu: cao/mạnh
Từ tệ nhất đến tốt nhất:

| Mức     | Cohesion                          | Mô tả ngắn                                                          |
| ------- | --------------------------------- | ------------------------------------------------------------------- |
| Tệ nhất | Coincidental (ngẫu nhiên)         | Các phần không liên quan gì, gom tùy tiện                           |
| Thấp    | Logical (logic)                   | Tác vụ giống nhau về loại (VD: gom hết I/O) nhưng khác chức năng    |
| Thấp    | Temporal (thời gian)              | Gom vì phải chạy cùng lúc (VD: init, log lỗi)                       |
| TB      | Procedural (thủ tục)              | Gom vì phải chạy theo đúng trình tự                                 |
| TB      | Communicational (truyền thông)    | Cùng thao tác trên 1 tập dữ liệu I/O                                |
| Cao     | Functional (chức năng) — lý tưởng | Mọi phần tử đều thiết yếu cho một hàm rõ ràng duy nhất              |
| Cao     | Informational (thông tin)         | Gom quanh 1 cấu trúc dữ liệu được đóng gói (OOP class, data hiding) |

> Note: khác với Coupling, thứ tự Cohesion không hoàn toàn tuyến tính "dở nhất → tốt nhất" theo 1 hàng — Functional được xem là lý tưởng nhất.

### Độ phức tạp kiến trúc hệ thống
Với module i bất kỳ:

1. Structural Complexity: S(i) = fout²(i) — fout(i) = fan-out = số module con bị gọi trực tiếp
2. Data Complexity: D(i) = v(i) / [fout(i) + 1] — v(i) = tổng biến vào/ra của module
3. System Complexity: C(i) = S(i) + D(i)

# PHẦN V: LẬP TRÌNH & KIỂM THỬ PHẦN MỀM

## Producer vs Consumer Reuse:

+ Producer Reuse: chủ động tạo component tổng quát, modular cao, để dùng lại về sau.
+ Consumer Reuse: tái sử dụng component có sẵn từ dự án khác, cần kiểm tra chất lượng/lịch sử test trước khi tích hợp.

Header Comment Block — khối chú thích đầu file, trả lời 5W1H: What (tên thành phần) – Who (tác giả) – Where (vị trí trong thiết kế hệ thống) – When (ngày viết/sửa) – Why (mục đích) – How (cấu trúc dữ liệu, thuật toán, luồng điều khiển).

### Black-box vs White-box Testing:
+ Black-box (hộp đen): test qua interface, không biết code bên trong.
+ White-box (hộp trắng): thiết kế test case dựa trên cấu trúc điều khiển/logic bên trong code.

### Chiến lược kiểm thử tích hợp (Integration Testing)

| Chiến lược        | Test trước                                            | Cần                    | Đặc điểm                  |
| ----------------- | ----------------------------------------------------- | ---------------------- | ------------------------- |
| Bottom-up         | Module cấp thấp                                       | Driver (trình gọi giả) | Dễ test đường dẫn cụ thể  |
| Top-down          | Module điều khiển cấp cao                             | Stub (module giả lập)  | Khó test đường dẫn cụ thể |
| Sandwich (Hybrid) | Chia 3 tầng: top (top-down), giữa, bottom (bottom-up) | Cả hai                 | Kết hợp ưu điểm 2 bên     |

> Note: mẹo nhớ — Bottom-up cần Driver (gọi từ dưới lên cần "người lái" gọi lên); Top-down cần Stub (giả lập phần dưới chưa có).

# PHẦN VI: ĐO LƯỜNG PHẦN MỀM & ĐỘ PHỨC TẠP
### Halstead Complexity Measures:
Đặt: n₁ = số toán tử phân biệt, n₂ = số toán hạng phân biệt, N₁ = tổng lượt toán tử, N₂ = tổng lượt toán hạng.

1. Độ dài ước tính: N_est = n₁log₂n₁ + n₂log₂n₂
2. Thể tích chương trình (Volume): V = (N₁+N₂) × log₂(n₁+n₂)
3. Độ khó (Difficulty): D = (n₁/2) × (N₂/n₂)
4. Công sức (Effort): E = V × D
5. Số lỗi dự đoán (Bugs): B = V / 3000

> Note: chuỗi tính phải theo đúng thứ tự n₁,n₂,N₁,N₂ → V → D → E → B, đề hay cho sẵn n₁,n₂,N₁,N₂ và yêu cầu tính ngược lên B.

### McCabe Cyclomatic Complexity (M)
Từ Control Flow Graph (CFG): M = E − N + 2P

+ E = số cạnh (control transitions)
+ N = số nút (statement/block)
+ P = số thành phần liên thông (P=1 với chương trình đơn ⟹ M = E − N + 2)

Quy tắc bắt buộc: điều kiện phức hợp (AND, OR) phải được phân rã thành từng điều kiện đơn (predicate node) riêng trên CFG.

Bảng tra độ phức tạp:
| M     | Đánh giá                                      |
| ----- | --------------------------------------------- |
| 1–10  | Cấu trúc tốt, khả năng test cao, chi phí thấp |
| 10–20 | Phức tạp, test trung bình, chi phí trung bình |
| 20–40 | Rất phức tạp, khả năng test thấp, chi phí cao |
| >40   | Không thể test được, chi phí cực cao          |

### Testing & Maintenance Metrics

1. Zero-Failure Testing — số giờ test cần thiết (t_zero) để đạt số lỗi mục tiêu f_target: t_zero = [ ln(f_target / (0.5×f_total)) / ln((0.5×f_total)/(f_total+f_target)) ] × t_h (f_total = tổng lỗi quan sát; t_h = giờ test tính đến lỗi cuối)
2. SMI — Software Maturity Index (độ ổn định qua các phiên bản): SMI = [ MT − (F_a + F_c + F_d) ] / MT (MT = tổng module hiện tại; F_a = module thêm mới; F_c = module thay đổi; F_d = module bị xóa so với bản trước)

# PHẦN VII: MÔ HÌNH ƯỚC LƯỢNG CHI PHÍ & NỖ LỰC
### Function Point Analysis (FPA)
Kỹ thuật ước lượng quy mô phần mềm không phụ thuộc ngôn ngữ, đếm 5 loại chức năng:

| Loại | Tên                      | Ý nghĩa                                                                 |
| ---- | ------------------------ | ----------------------------------------------------------------------- |
| EI   | External Inputs          | Dữ liệu từ ngoài vào để cập nhật ILF                                    |
| EO   | External Outputs         | Dữ liệu tính toán/phát sinh đi ra (report, file, graph)                 |
| EQ   | External Inquiries       | Truy vấn đơn giản (search + retrieve), không có dữ liệu tính toán       |
| ILF  | Internal Logical Files   | Nhóm dữ liệu nằm trong hệ thống, được cập nhật bởi EI                   |
| EIF  | External Interface Files | Nhóm dữ liệu chỉ để tham chiếu, nằm ngoài hệ thống, do app khác quản lý |

## Bảng trọng số độ phức tạp:

| Loại chức năng | Thấp | Trung bình | Cao |
| -------------- | ---- | ---------- |
| EI             | 3    | 4          | 6   |
| EO             | 4    | 5          | 7   |
| EQ             | 3    | 4          | 6   |
| ILF            | 7    | 10         | 15  |
| EIF            | 5    | 7          | 10  |

## Công thức tính:

1. Unadjusted Function Points: UFP = a₁·EI + a₂·EO + a₃·EQ + a₄·ILF + a₅·EIF (a_k tra theo bảng trọng số)
2. Technical Complexity Factor: TCF = 0.65 + 0.01 × Σ(14 SCᵢ) (SCᵢ: điểm ảnh hưởng 0–5 của 14 đặc trưng hệ thống)
3. Adjusted Function Points: FP = UFP × TCF
4. Estimated Code Size: LOC = AVC × FP (AVC: dòng lệnh trung bình/FP — C#=55, Java=55, C++=55, C=128, SQL=13)

> Note: thứ tự tính luôn là UFP → TCF → FP → LOC, không đảo ngược.

### COCOMO II — Post-Architecture Model

1. Công thức nỗ lực: PM = a × S^b × ∏(17 EMᵢ)
   + a = 2.5 (hằng số thực nghiệm)
   + S = kích thước phần mềm (KLOC)
   + EMᵢ = 17 Effort Multipliers / Cost Drivers (VD: RELY, CPLX, ACAP, PCAP...)
2. Hệ số mũ b (Scale Factor): b = 1.01 + 0.01 × Σ(5 SFᵢ) 5 Scale Factors (Rất thấp → Cực cao):
   + PREC (Precedentedness) — mức độ quen thuộc với đội (4.05→0)
   + FLEX (Development Flexibility) — cứng nhắc vs linh hoạt (6.07→0)
   + RESL (Architecture/Risk Resolution) — mức phân tích rủi ro (4.22→0)
   + TEAM (Team Cohesion) — mức hợp tác nhóm (4.94→0)
   + PMAT (Process Maturity) — độ chín quy trình theo CMM (4.54→0)
> Note: điểm SF càng cao (Very Low → dự án càng mới/rủi ro) thì b càng lớn → PM tăng phi tuyến theo size. Ngược lại dự án quen thuộc, quy trình chín (Extra High) → SF gần 0 → b gần 1.01 (gần tuyến tính).

# GHI CHÚ ÔN TẬP NHANH (Quick Recap)
+ Error → Defect → Failure: chuỗi nhân quả nhớ kỹ.
+ Validation = đúng sản phẩm | Verification = đúng cách làm.
+ Coupling thấp – Cohesion cao = mục tiêu thiết kế tốt.
+ Bottom-up → Driver | Top-down → Stub.
+ Công thức Halstead, McCabe, FPA, COCOMO II đều có trong đề dạng tính toán — nắm chắc thứ tự các bước và ý nghĩa từng biến quan trọng hơn học vẹt công thức.