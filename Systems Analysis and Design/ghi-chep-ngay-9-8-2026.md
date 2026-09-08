# Ghi chép ngày 9/8/2026 — Phân tích Thiết kế Hệ thống (CT112H)
### Chương 1: Introduction

---

## 1. Thông tin chung môn học

- **Tên môn:** System Analysis and Design (Phân tích Thiết kế Hệ thống)
- **Mã môn:** CT112H
- **Số tín chỉ:** 3 (30 tiết lý thuyết + 30 tiết thực hành)
- **Cách tính điểm:**
  - Đồ án nhóm **hoặc** thi giữa kỳ: 40%
  - Thi cuối kỳ: 60%

**Ý nghĩa thực tế:** đây là môn "nặng" thực hành nhóm — bạn cần chuẩn bị tinh thần làm việc nhóm nghiêm túc vì phần lớn điểm quá trình (40%) có thể đến từ đồ án, không chỉ học thuộc lý thuyết.

## 2. Mục tiêu môn học

**Về kiến thức**, sau môn này bạn phải nắm được:
- Môi trường phát triển hệ thống (System Development Environment)
- Cách phân tích yêu cầu người dùng (User requirements analysis)
- Thành phần dữ liệu của hệ thống (Data component)
- Thành phần xử lý của hệ thống (Processing component)
- Tương tác người–máy (Human Computer Interaction)

**Về kỹ năng**, bạn phải làm được:
- Xác định yêu cầu người dùng chính xác
- Thiết kế mô hình dữ liệu (data model)
- Thiết kế lưu đồ dữ liệu (Data Flow Diagram – DFD)
- Làm việc nhóm và trình bày báo cáo kỹ thuật

**Áp dụng thực tế:** đây gần như là bản mô tả công việc của một **Business Analyst / System Analyst** thực thụ trong ngành — người phải vừa hiểu nghiệp vụ (thu thập yêu cầu), vừa hiểu kỹ thuật (mô hình hóa dữ liệu, DFD) để làm cầu nối giữa khách hàng và đội lập trình.

## 3. Nhiệm vụ của sinh viên

- Chú ý nghe giảng trên lớp
- Chủ động, tích cực hoàn thành bài tập
- **Đối chiếu với lời giải của giảng viên** để:
  - Phát hiện điểm chưa nhất quán trong bài phân tích của mình
  - Phát hiện các thành phần thiết kế còn yếu
- Rèn tư duy phản biện và khả năng phát hiện vấn đề qua thực hành

**Gợi ý áp dụng:** thói quen "tự làm trước → so với đáp án → tự tìm lỗi sai" chính là cách một analyst thật sự học nghề — vì phân tích hệ thống không có đáp án tuyệt đối, chỉ có đáp án "hợp lý hơn/kém hợp lý hơn", nên việc so sánh và tự phản biện quan trọng hơn học thuộc.

## 4. Các khái niệm cơ bản

### 4.1. Hệ thống (System) là gì?
Theo từ điển Merriam-Webster: **hệ thống là một nhóm các thành phần tương tác hoặc phụ thuộc lẫn nhau, cùng tạo thành một thể thống nhất.**

Ví dụ minh họa trong slide: hệ mặt trời, hệ thống giao thông công cộng, hệ thống máy tính, hệ thống thông tin.

### 4.2. Dữ liệu (Data) vs Thông tin (Information)
Đây là khái niệm hay bị nhầm lẫn nhất, cần phân biệt rõ:

| | Định nghĩa |
|---|---|
| **Dữ liệu (Data)** | Sự kiện thô, chưa được tổ chức, cần được xử lý. Đơn giản, đôi khi ngẫu nhiên, và **vô nghĩa nếu chưa được sắp xếp/cấu trúc hóa**. |
| **Thông tin (Information)** | Dữ liệu **đã được xử lý, tổ chức hoặc trình bày trong một ngữ cảnh cụ thể** để trở nên có ý nghĩa và hữu ích. |

**Ví dụ trong slide:** điểm tổng kết của một sinh viên, phân bố điểm của một lớp học — đây là *thông tin* vì đã qua xử lý (tính trung bình, thống kê) từ *dữ liệu* thô (điểm từng bài kiểm tra).

**Ví dụ thực tế dễ hình dung:** Khi bạn quẹt thẻ sinh viên vào máy điểm danh, mỗi lần quẹt tạo ra một **dữ liệu** (giờ, mã sinh viên). Nhưng khi hệ thống tổng hợp lại thành "sinh viên A vắng 3 buổi trong tháng 9" thì đó là **thông tin** — thứ giảng viên/phòng đào tạo thực sự dùng để ra quyết định.

### 4.3. Hệ thống thông tin (Information System)
Theo Merriam-Webster: là **hệ thống máy tính dùng để thu thập, tạo lập, lưu trữ, xử lý và phân phối dữ liệu/thông tin.**

## 5. Các thành phần của Hệ thống thông tin

Một hệ thống thông tin gồm 5 thành phần cốt lõi:

1. **Hardware** — phần cứng (máy chủ, máy trạm, thiết bị mạng...)
2. **Software** — phần mềm (ứng dụng, hệ điều hành...)
3. **Data** — dữ liệu (cơ sở dữ liệu lưu trữ)
4. **Networks** — mạng (kết nối giữa các thành phần)
5. **People** — con người (người dùng, quản trị viên...)
6. **Procedures** — quy trình, thủ tục vận hành

**Áp dụng thực tế:** khi phân tích bất kỳ hệ thống nào (ví dụ hệ thống quản lý thư viện của trường), bạn nên tự hỏi lần lượt: phần cứng gì cần có? phần mềm nào? dữ liệu nào cần lưu? mạng kết nối ra sao? ai là người dùng? quy trình mượn/trả sách thế nào? — đây chính là checklist 6 thành phần bên trên.

## 6. Các loại Hệ thống thông tin (kèm ví dụ thực tế)

Slide liệt kê 6 loại chính, xếp theo cấp độ từ tác nghiệp (vận hành hàng ngày) lên đến chiến lược (quyết định cấp cao):

### a) Transaction Processing Systems (TPS) — Hệ thống xử lý giao dịch
- Thực hiện thu thập, lưu trữ, chỉnh sửa, truy xuất **dữ liệu giao dịch** của doanh nghiệp.
- Chỉ xử lý các giao dịch **có cấu trúc, được định nghĩa sẵn**.
- Thời gian phản hồi ngắn, nhưng không hẳn là thời gian thực (real-time).
- **Ví dụ thực tế:** hệ thống thanh toán quẹt thẻ POS tại cửa hàng, hệ thống bán vé/đặt phòng của các đại lý du lịch (Internet Booking Engine), phần mềm order tại nhà hàng — đây đều là các hệ thống ghi nhận từng giao dịch một cách có cấu trúc.

### b) Management Information Systems (MIS) — Hệ thống thông tin quản lý
- Hỗ trợ **ra quyết định**, phối hợp công việc, duy trì kiểm soát, cung cấp thông tin xuyên suốt tổ chức.
- Mục tiêu cuối cùng: tăng giá trị và lợi nhuận của tổ chức bằng cách cung cấp cho nhà quản lý thông tin **kịp thời và phù hợp**.
- **Ví dụ thực tế:** các phân hệ trong hệ thống ERP như CRM (quản lý khách hàng), HRM (quản lý nhân sự), FAM (quản lý tài chính) — đây là những hệ thống MIS phổ biến trong doanh nghiệp.

### c) Office Automation Systems (OAS) — Hệ thống tự động hóa văn phòng
- Giải pháp phần cứng/phần mềm giúp **truyền dữ liệu giữa các bộ phận trong tổ chức**, đơn giản hóa quy trình, tự động hóa các tác vụ hành chính.
- **Ví dụ thực tế:** bộ công cụ văn phòng như email nội bộ, lịch họp chia sẻ, hệ thống quản lý văn bản/công văn điện tử.

### d) Knowledge Management Systems (KMS) — Hệ thống quản lý tri thức
- Cho phép **tạo, chia sẻ, lưu giữ và phát triển** nguồn tri thức, đảm bảo sử dụng tối ưu trong tổ chức để hỗ trợ ra quyết định và đổi mới.
- Lợi ích: tăng năng suất, cải thiện hiệu quả quản lý, tăng sự hài lòng của khách hàng, thu hút và giữ nhân tài, khuyến khích học tập/chia sẻ tri thức.
- **Ví dụ thực tế:** hệ thống wiki nội bộ doanh nghiệp, cơ sở dữ liệu tài liệu/kinh nghiệm dùng chung (ví dụ Confluence, SharePoint dùng làm kho tri thức).

### e) Decision Support Systems (DSS) — Hệ thống hỗ trợ ra quyết định
- Kết hợp **dữ liệu và các mô hình phân tích phức tạp/công cụ phân tích dữ liệu** để hỗ trợ ra quyết định cho các vấn đề **bán cấu trúc và phi cấu trúc**.
- Phân tích khối lượng lớn dữ liệu phi cấu trúc, tích lũy thông tin để giúp giải quyết vấn đề.
- Cấu trúc gồm: DSS Models, OLAP Tools, Data Mining Tools kết nối với DSS Database (nhận dữ liệu từ nguồn ngoài và từ TPS), qua giao diện người dùng.
- **Ví dụ thực tế:** công cụ phân tích dữ liệu bán hàng để dự báo xu hướng (dùng OLAP/data mining), hệ thống hỗ trợ lập kế hoạch tồn kho dựa trên dữ liệu lịch sử.

### f) Executive Support System (ESS) — Hệ thống hỗ trợ điều hành
- Cho phép **truy cập nhanh và dễ dàng vào dữ liệu quan trọng**, hỗ trợ ra quyết định **chiến lược**, tập trung vào các chỉ số hiệu suất chính (KPI) và ưu tiên của tổ chức.
- **Ví dụ thực tế:** dashboard điều hành (executive dashboard) mà ban giám đốc dùng để xem tổng quan doanh thu, KPI toàn công ty theo thời gian thực.

**Mẹo phân biệt nhanh (áp dụng khi làm bài tập):** hãy hỏi "hệ thống này phục vụ **cấp nào** trong tổ chức?"
- Nhân viên tác nghiệp hàng ngày → TPS
- Quản lý cấp trung → MIS / KMS / OAS
- Phân tích ra quyết định phức tạp → DSS
- Ban lãnh đạo cấp cao → ESS

## 7. Vì sao cần phân tích & thiết kế hệ thống?

### 7.1. Vòng đời phát triển phần mềm (SDLC) — 7 giai đoạn
1. **Planning** — Lập kế hoạch
2. **Define Requirements** — Xác định yêu cầu
3. **Design & Prototyping** — Thiết kế & làm mẫu thử
4. **Software Development** — Phát triển phần mềm
5. **Testing** — Kiểm thử
6. **Deployment** — Triển khai
7. **Operations & Maintenance** — Vận hành & bảo trì

**Vị trí của môn học này trong vòng đời:** Phân tích Thiết kế Hệ thống nằm chủ yếu ở giai đoạn 2 và 3 (Define Requirements, Design & Prototyping) — tức là *trước khi* bắt tay viết code (giai đoạn 4). Đây là lý do môn này quan trọng: sai ở bước phân tích/thiết kế sẽ kéo theo chi phí sửa lỗi rất lớn ở các giai đoạn sau.

### 7.2. Mục đích của Phân tích hệ thống (System Analysis)
- Hiểu hệ thống cần xây dựng
- Thu thập và diễn giải dữ liệu, xác định vấn đề, chia nhỏ hệ thống thành các thành phần
- Là kỹ thuật giải quyết vấn đề nhằm cải thiện hệ thống và đảm bảo mọi thành phần hoạt động hiệu quả
- Trả lời các câu hỏi: **"Hệ thống nên làm gì? Vì sao nên làm vậy? Có khả thi không?"**

### 7.3. Mục đích của Thiết kế hệ thống (System Design)
- Xác định các cách tiếp cận để xây dựng hệ thống
- Đánh giá các phương án giải pháp khác nhau
- Chọn chiến lược triển khai hiệu quả nhất
- Trả lời câu hỏi: **"Yêu cầu/chức năng này nên được thực hiện như thế nào?"**

**Phân biệt cốt lõi (rất hay bị nhầm khi thi):**
- **Phân tích = WHAT/WHY** (hệ thống làm gì, vì sao, có khả thi không)
- **Thiết kế = HOW** (làm như thế nào)

## 8. Để trở thành một Systems Analyst

**Kiến thức và kỹ năng cần có**, chia làm 3 nhóm song song (kiến thức đi kèm kỹ năng tương ứng):
- **Technical knowledge ↔ Technical skills** — kiến thức kỹ thuật và kỹ năng kỹ thuật
- **Business knowledge ↔ Business skills** — kiến thức nghiệp vụ và kỹ năng nghiệp vụ
- **People knowledge ↔ People skills** — kiến thức về con người và kỹ năng giao tiếp/làm việc với con người

**Các bên liên quan (stakeholders) mà một Systems Analyst thường xuyên làm việc cùng:**
- Managers (quản lý)
- External companies (công ty bên ngoài)
- System stakeholders (các bên liên quan hệ thống)
- Software programmers (lập trình viên)
- Users (người dùng)
- Vendors and suppliers (nhà cung cấp)
- Technical specialists (chuyên gia kỹ thuật)

**Áp dụng thực tế:** điều này giải thích vì sao môn học nhấn mạnh kỹ năng làm việc nhóm và trình bày báo cáo (mục 2) — vì công việc thật của một Systems Analyst không chỉ là ngồi viết tài liệu một mình, mà phải giao tiếp với rất nhiều nhóm người có nền tảng khác nhau (quản lý, lập trình viên, người dùng cuối, nhà cung cấp...).

## 9. Tài liệu tham khảo (do giảng viên cung cấp)
- Course slides
- *System Analysis and Design*, Trương Quốc Định, Phan Tấn Tài, 2018
- *Modern System Analysis and Design*, Jeffrey A. Hoffer, Joey F. George, Joseph S. Valacich, 2002
- *Understanding your users — A practical guide to user requirements: Methods, Tools & Techniques*, Catherine Courage, Kathy Baxter, 2005
- *Business Process Model and Notation* — https://www.bpmn.org/

---

## Tóm tắt nhanh (đọc lại 30 giây trước khi vào lớp/ôn thi)
1. Hệ thống = tập hợp các phần tương tác nhau tạo thành một thể thống nhất.
2. Dữ liệu là thô, thông tin là dữ liệu đã qua xử lý và có ý nghĩa.
3. Hệ thống thông tin gồm 6 thành phần: Hardware, Software, Data, Networks, People, Procedures.
4. 6 loại hệ thống thông tin xếp theo cấp độ tổ chức: TPS (tác nghiệp) → MIS/OAS/KMS (quản lý) → DSS (phân tích) → ESS (điều hành).
5. SDLC có 7 giai đoạn; phân tích & thiết kế hệ thống nằm ở giai đoạn 2–3, trước khi code.
6. Phân tích trả lời WHAT/WHY, Thiết kế trả lời HOW.
7. Systems Analyst cần 3 nhóm năng lực song song: kỹ thuật, nghiệp vụ, con người.
