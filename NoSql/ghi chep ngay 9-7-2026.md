# Ghi chép: NoSQL Databases (CT113H) — Lecture 1: Why NoSQL, Principles, Overview
**GV: N.C. Danh — Khoa Công nghệ phần mềm, Trường CNTT&TT, ĐH Cần Thơ**
**Ghi chép ngày: 07/09/2026 — tổng hợp đến slide 36 (hết bài)**

---

## 0. Trước khi vào bài — bức tranh tổng thể

Bài giảng này trả lời đúng 1 câu hỏi lớn: **"Tại sao RDBMS (SQL truyền thống) không còn đủ nữa, và NoSQL giải quyết vấn đề gì?"**

Mạch logic của cả bài:
1. Thế giới dữ liệu bây giờ khác xưa rất nhiều (Big Data, Big Users, Cloud) →
2. RDBMS tốt nhưng có giới hạn khi gặp dữ liệu khổng lồ, phân tán →
3. Nên người ta sinh ra NoSQL để giải quyết đúng những giới hạn đó →
4. NoSQL không phải 1 công nghệ, mà là 4 "trường phái" khác nhau (key-value, document, column-family, graph), mỗi loại giải quyết 1 kiểu bài toán riêng.

Nhớ đúng mạch này là bạn đã nắm được 80% bài rồi, phần còn lại chỉ là chi tiết.

---

## 1. Các xu hướng hiện tại (Current Trends)

### 1.1. Big Data — dữ liệu tăng theo cấp số nhân
Biểu đồ trong slide cho thấy: dữ liệu (đặc biệt là dữ liệu **bán cấu trúc / phi cấu trúc** — text, log, blog, tweet, video...) tăng vọt từ năm 2000 đến 2014, từ gần 0 lên tới gần 3 zettabyte, và còn tiếp tục tăng theo hàm mũ.

→ Ý nghĩa thực tế: trước đây dữ liệu chủ yếu là **structured** (bảng, số liệu có khuôn mẫu rõ ràng — hợp với RDBMS). Bây giờ phần lớn dữ liệu mới sinh ra lại là **semi-structured/unstructured** — khó nhét vừa vào bảng cứng nhắc của RDBMS.

Đặc trưng của Big Data được gói gọn trong **3V**:
- **Volume** — khối lượng (VD: 640 TB dữ liệu sinh ra chỉ trong 1 chuyến bay xuyên đại dương của Boeing)
- **Velocity** — tốc độ sinh ra/xử lý dữ liệu (streaming, real-time)
- **Variety** — đa dạng định dạng (JSON, log, ảnh, video, sensor...)

Định nghĩa chính thức (Gartner, 2012), diễn giải lại: Big Data là tài sản thông tin có volume/velocity/variety cao đến mức **cần cách xử lý mới** để khai thác được giá trị (ra quyết định, tối ưu quy trình...).

**Nguồn dữ liệu lớn (Sources of Big Data)** theo slide:
- Mạng xã hội (dữ liệu lớn nhưng volume tương đối giới hạn so với các nguồn khác)
- Log của web/email server, router (tăng không giới hạn)
- Mạng cảm biến (sensor networks) — dự kiến tăng nhanh nhất
- IoT (Internet of Things)
- Máy móc điều khiển bằng máy tính, ví dụ máy bay Boeing (640 TB/chuyến bay xuyên đại dương)

### 1.2. Big Users — số người dùng bùng nổ
Theo slide: hơn 2 tỷ người dùng online toàn cầu, 35 tỷ giờ online, hơn 1 tỷ người dùng smartphone. Một hệ thống web hoàn toàn có thể đạt **hàng triệu người dùng chỉ trong vài tháng**. → Hệ quản trị dữ liệu phải chịu được tải ghi/đọc cực lớn, đột biến, không thể dự đoán trước như thời RDBMS truyền thống thiết kế.

### 1.3. Cloud Computing
Mọi thứ dần chuyển lên Cloud với 3 tầng dịch vụ quen thuộc:
- **IaaS** (Infrastructure as a Service) — thuê hạ tầng máy chủ
- **PaaS** (Platform as a Service) — thuê nền tảng để triển khai app
- **SaaS** (Software as a Service) — dùng phần mềm trực tiếp qua mạng

→ Đặc điểm quan trọng: hệ thống trên Cloud có tính **phân tán (distributed)** và **linh hoạt (flexible)** — đây chính là môi trường mà NoSQL sinh ra để phục vụ tốt nhất.

### 1.4. Cách xử lý dữ liệu truyền thống — để bạn phân biệt rõ 3 khái niệm hay bị nhầm
- **OLTP** (Online Transaction Processing): DB truyền thống, dùng để lưu/truy vấn, nhiều người dùng cùng lúc (VD: hệ thống bán hàng, ngân hàng).
- **OLAP** (Online Analytical Processing / Data Warehousing): trả lời các truy vấn phân tích đa chiều — báo cáo tài chính, marketing, dự báo, ngân sách...
- **RTAP** (Real-Time Analytic Processing): dữ liệu được thu thập và xử lý **theo thời gian thực** (streaming), kết hợp cả dữ liệu real-time lẫn dữ liệu lịch sử. Đây là kiến trúc/công nghệ đặc trưng của thời đại Big Data.

### 1.5. Công nghệ cho Big Data (liệt kê để biết mặt)
Distributed file systems (GFS, HDFS), MapReduce (và các mô hình lập trình phân tán khác), NoSQL databases, Data Warehouses, Grid/Cloud computing, Large-scale machine learning.

---

## 2. RDBMS — vì sao mạnh nhưng vẫn không đủ cho Big Data

### 2.1. RDBMS là gì (ôn lại nhanh)
- Đề xuất bởi Edgar Codd (IBM, 1970) — công nghệ database chủ đạo suốt nhiều thập kỷ.
- Dữ liệu = các **bảng (table)**, mỗi dòng (tuple) là 1 object, mỗi cột có kiểu dữ liệu (domain) cố định.
- Mỗi bảng có 1 khóa (key) để định danh duy nhất từng dòng.
- Các bảng liên kết với nhau qua **khóa ngoại (foreign key)** — đây chính là điều làm nên RDBMS: dữ liệu được **chuẩn hóa (normalize)**, tách nhỏ ra nhiều bảng để tránh dư thừa, rồi khi cần thì `JOIN` lại.

Ví dụ trong slide: bảng `Students`, bảng `Courses`, bảng trung gian `Takes_Course` nối 2 bảng kia qua khóa ngoại. Muốn biết ai học lớp `1001` thì viết:
```sql
SELECT Name FROM Students NATURAL JOIN Takes_Course WHERE ClassID = 1001
```
→ Đây chính là bản chất SQL: dữ liệu tách rời, truy vấn thì ghép lại.

### 2.2. Giá trị thật sự của RDBMS (đừng nghĩ RDBMS "lỗi thời")
- Mô hình dữ liệu gần như chuẩn hóa toàn ngành (ai học DB cũng biết SQL).
- Công nghệ chín muồi: index, tối ưu truy vấn, tổ chức vật lý dữ liệu đã được nghiên cứu hàng chục năm.
- **ACID** — cơ chế transaction cực kỳ đáng tin cậy:
  - **A**tomicity (toàn vẹn — hoặc làm hết hoặc không làm gì)
  - **C**onsistency (nhất quán — dữ liệu luôn đúng ràng buộc)
  - **I**solation (cô lập — nhiều transaction chạy song song không phá nhau)
  - **D**urability (bền vững — đã commit thì không mất dù crash)
- Tích hợp dễ dàng giữa nhiều ứng dụng qua "shared database integration".
- Ổn định, quen thuộc, có hỗ trợ thương mại mạnh (Oracle, MySQL...).

### 2.3. Vậy vấn đề nằm ở đâu? — Bảng đối chiếu Trends vs Requirements (quan trọng, nên nhớ)

| Xu hướng (Trend) | Yêu cầu mới phát sinh (Requirement) |
|---|---|
| Volume dữ liệu tăng | Cần khả năng mở rộng (scalability) thật sự: phân tán dữ liệu, quản lý tài nguyên động, **scale horizontally** (thêm máy chứ không nâng cấp máy) |
| Cloud Computing (IaaS) | Cùng yêu cầu trên |
| Velocity dữ liệu cao | Cần chịu được **update cực nhiều** và liên tục |
| Big Users | Cần **read throughput** khổng lồ (đọc nhanh, đọc nhiều cùng lúc) |
| Variety dữ liệu | Cần **schema linh hoạt** — chấp nhận dữ liệu bán cấu trúc, không cần khai báo trước 100% |

### 2.4. Vì sao RDBMS đuối sức trước những yêu cầu này
- RDBMS cần **schema biết trước (a priori)** — khai báo bảng, cột, kiểu dữ liệu trước khi có dữ liệu. Nhưng dữ liệu thực tế bây giờ lại "tự nhiên linh hoạt" (naturally flexible) — không hợp với khuôn cứng.
- **Chuẩn hóa (normalization/3NF)** tách dữ liệu ra nhiều bảng nhỏ → khi dữ liệu lớn, việc `JOIN` liên tục để ghép lại trở nên **kém hiệu quả (inefficient)**.
- **Transaction ACID đầy đủ** rất tốt cho 1 máy chủ, nhưng trong môi trường **phân tán** (nhiều server, nhiều vùng địa lý), việc đảm bảo ACID đầy đủ trở nên **rất chậm và tốn kém (very inefficient in distributed environment)** — vì các máy phải "khóa" và đồng bộ với nhau liên tục.

→ Đây chính là lý do NoSQL ra đời: **đánh đổi bớt ACID/chuẩn hóa để đổi lấy khả năng scale ngang và tốc độ trên hệ phân tán.**

---

## 3. NoSQL Databases là gì

### 3.1. Tên gọi "NoSQL" — một cái tên hơi... tình cờ
- Thuật ngữ "NoSQL" xuất hiện lần đầu cuối thập niên 90 (Carlo Strozzi) để chỉ 1 công nghệ hoàn toàn khác, không liên quan đến làn sóng NoSQL hiện nay.
- Cách hiểu "Not Only SQL" cũng không hoàn toàn chuẩn, vì nhiều RDBMS hiện đại cũng "not just SQL" (có thêm các tính năng khác).
- Trích dẫn thẳng từ sách *NoSQL Distilled* (Sadalage & Fowler, 2012) — cuốn sách gối đầu giường của chủ đề này: **"NoSQL is an accidental term with no precise definition"** — tức là bản thân giới chuyên môn cũng thừa nhận đây là 1 cái tên ngẫu nhiên, không có định nghĩa chính xác tuyệt đối.
- Thuật ngữ này được dùng chính thức lần đầu tại 1 buổi meetup không chính thức năm 2009 ở San Francisco, với các bài trình bày về Voldemort, Cassandra, Dynomite, HBase, Hypertable, CouchDB, MongoDB.

### 3.2. Đặc điểm chung của NoSQL (theo Sadalage & Fowler, 2012)
NoSQL = nhóm công nghệ database mà (đa phần):
1. **Không dùng mô hình quan hệ** (không bảng, không SQL chuẩn)
2. **Thiết kế để chạy trên cluster lớn** — scale ngang (horizontal)
3. **Không có schema cố định** — có thể thêm field tự do vào bất kỳ record nào
4. Thường là **mã nguồn mở (open source)**
5. Sinh ra để đáp ứng nhu cầu của các "đại gia" web thế kỷ 21 (Google, Amazon, Facebook...)

Đặc điểm khác (thường đúng, không phải luật bắt buộc):
- Hỗ trợ **replication** (nhân bản dữ liệu) dễ dàng → chịu lỗi tốt, đọc nhanh hơn
- API đơn giản
- **Eventually consistent** (nhất quán cuối cùng) thay vì ACID nghiêm ngặt — nghĩa là sau 1 khoảng thời gian ngắn, mọi bản sao dữ liệu sẽ đồng bộ, chứ không cần đồng bộ ngay tức thì như ACID.

### 3.3. 4 tính chất cốt lõi cần nhớ của NoSQL
1. **Scalability tốt** — scale ngang (thêm máy) thay vì scale dọc (nâng cấp 1 máy)
2. **Schema động (dynamic)** — mỗi loại NoSQL linh hoạt ở mức khác nhau
3. **Đọc hiệu quả** — chấp nhận tốn thời gian lưu (ghi phức tạp hơn 1 chút để tổ chức dữ liệu tốt) để đổi lấy đọc cực nhanh, vì **giữ thông tin liên quan gần nhau** (khác hẳn tư duy chuẩn hóa/tách bảng của RDBMS)
4. **Tiết kiệm chi phí** — chạy được trên phần cứng phổ thông (commodity hardware), thường mã nguồn mở

### 3.4. Thách thức thật của NoSQL (đừng nghĩ nó toàn diện hơn RDBMS)
1. **Độ chín (maturity)** — đang tốt lên nhưng RDBMS đã có 50+ năm kinh nghiệm
2. **Hỗ trợ người dùng** — ít có support chuyên nghiệp kiểu Oracle
3. **Vận hành (administration)** — hệ thống phân tán lớn đòi hỏi kỹ năng quản trị cao
4. **Chuẩn truy cập dữ liệu** — RDBMS có SQL thống nhất, thế giới NoSQL "hoang dã" hơn, mỗi hệ 1 kiểu API/query riêng
5. **Thiếu chuyên gia** — không đủ người có kinh nghiệm sâu về NoSQL

### 3.5. Kết luận thực tế: RDBMS KHÔNG biến mất
- RDBMS vẫn lý tưởng cho dữ liệu có cấu trúc rõ ràng, cần độ tin cậy cao — vẫn "chân ái" trong nhiều bài toán.
- RDBMS giờ chỉ là **1 lựa chọn trong nhiều lựa chọn** lưu trữ dữ liệu.
- Khái niệm quan trọng: **Polyglot persistence** — dùng **nhiều loại data store khác nhau cho các tình huống khác nhau trong cùng 1 hệ thống**, thay vì ép tất cả vào 1 loại DB duy nhất. (VD: 1 công ty có thể dùng RDBMS cho dữ liệu giao dịch, Redis cho cache, MongoDB cho dữ liệu sản phẩm linh hoạt, Neo4j cho phân tích quan hệ bạn bè...)
- 2 xu hướng đang song song diễn ra: NoSQL dần bổ sung các tính năng chuẩn của RDBMS (transaction tốt hơn...), còn RDBMS cũng học hỏi nguyên lý NoSQL (hỗ trợ JSON, scale ngang tốt hơn...).

---

## 4. Bốn loại NoSQL Databases — phần quan trọng nhất, cần nắm chắc

Biểu đồ trong slide sắp xếp 4 loại theo trục **Size (kích thước dữ liệu mỗi record)** và **Complexity (độ phức tạp của mối quan hệ dữ liệu)**, theo thứ tự tăng dần độ phức tạp:
**Key-Value → Column Families → Document Databases → Graph Databases**

### Trước hết: MapReduce — "động cơ" chạy phía sau nhiều hệ NoSQL
- Là mô hình lập trình chung để xử lý phân tán các tập dữ liệu lớn, chạy trên hệ thống file phân tán (VD HDFS).
- Người dùng chỉ cần viết đúng 2 hàm: **map** (chia nhỏ, xử lý song song) và **reduce** (gộp kết quả lại).
- Quy trình: dữ liệu đầu vào được chia thành nhiều `split` → nhiều `worker` chạy hàm map song song → ghi ra file tạm → các `worker` khác đọc và chạy `reduce` → ghi ra file kết quả cuối.
- Cài đặt phổ biến: **Hadoop MapReduce**, **Spark**, Amazon Elastic MapReduce, và cũng là nền tảng bên trong của MongoDB, Riak, Cassandra ở một số khía cạnh.

### 4.1. Key-Value Stores — đơn giản nhất
**Bản chất:** giống 1 cái hash table/map khổng lồ. Bạn chỉ có 2 cột: `ID` (khóa chính) và `DATA` (giá trị — coi như 1 khối dữ liệu không rõ cấu trúc bên trong, BLOB).

**3 thao tác cơ bản duy nhất:**
```
put(key, value)      // lưu giá trị theo khóa
value := get(key)    // lấy giá trị theo khóa
delete(key)           // xóa theo khóa
```

**Kiến trúc:**
1. **Embedded** — DB chạy như 1 thư viện ngay trong ứng dụng của bạn (VD: LevelDB, RocksDB)
2. **Phân tán quy mô lớn** — thường tổ chức theo **Distributed Hash Table (DHT)**: các node xếp thành vòng, mỗi node chịu trách nhiệm lưu 1 khoảng key nhất định (VD: node B, C, D lưu các key nằm trong khoảng A→B).

**Ưu điểm:** đơn giản, hiệu năng cực cao, dễ scale.
**Đại diện thật:** Amazon DynamoDB, Redis, Riak, Memcached, LevelDB, RocksDB, Project Voldemort, Berkeley DB.

**Ứng dụng thực tế điển hình:** cache (session người dùng, giỏ hàng tạm), bảng tra cứu nhanh theo ID — bất cứ khi nào bạn CHỈ cần tra theo khóa, không cần lọc theo nội dung bên trong giá trị.

### 4.2. Document Databases — key-value "thông minh hơn"
**Bản chất:** vẫn là key-value, nhưng phần **value giờ là 1 "document" tự mô tả (self-describing)** — có cấu trúc cây phân cấp, thường là JSON/BSON/XML. Điểm khác biệt cốt lõi so với key-value thường: **DB có thể "nhìn vào bên trong" document để đánh index và truy vấn theo field**, chứ không chỉ tra theo khóa.

Ví dụ thật từ slide (2 document trong cùng 1 collection, khác schema nhau — điều RDBMS không cho phép nhưng document DB thì được):
```json
key=3 -> {
  "personID": 3,
  "firstname": "Martin",
  "likes": ["Biking", "Photography"],
  "lastcity": "Boston",
  "visited": ["NYC", "Paris"]
}

key=5 -> {
  "personID": 5,
  "firstname": "Pramod",
  "citiesvisited": ["Chicago", "London", "NYC"],
  "addresses": [
    {"state": "AK", "city": "DILLINGHAM"},
    {"state": "MH", "city": "PUNE"}
  ],
  "lastcity": "Chicago"
}
```
→ Chú ý: document key=3 có field `likes`, `visited`; document key=5 lại có `citiesvisited`, `addresses` — 2 document trong cùng collection nhưng **không cùng schema**. Đây chính là "flexible schema" nói ở phần trên.

Truy vấn (ví dụ cú pháp MongoDB, đối chiếu song song với SQL):
```sql
-- SQL
SELECT * FROM users
SELECT * FROM users WHERE personID = 3
SELECT firstname, lastcity FROM users WHERE personID = 5
```
```javascript
// MongoDB — tương đương
db.users.find()
db.users.find({ "personID": 3 })
db.users.find({ "personID": 5 }, {firstname: 1, lastcity: 1})
```

**Đại diện thật:** MongoDB, CouchDB, OrientDB, RavenDB, Amazon DynamoDB, PostgreSQL (hỗ trợ JSONB — chính là ví dụ RDBMS "học" NoSQL đã nói ở trên).

**Ứng dụng thực tế điển hình:** hồ sơ người dùng, catalog sản phẩm (mỗi sản phẩm có thuộc tính khác nhau: áo có size/màu, sách có tác giả/số trang), nội dung CMS/blog.

### 4.3. Column-family Stores (Wide-column / Columnar)
**Bản chất:** mỗi dòng (row) được định danh bởi **row key**, nhưng mỗi row có thể có **rất nhiều cột**, và các cột được nhóm thành **column family** — tức là nhóm các cột **hay được truy cập cùng nhau**.

Ví dụ thật từ slide: 1 khách hàng có `row key = 1234`, có 2 column family:
- Family `profile` chứa các cột: `name`, `billingAddress`, `payment` — vì mấy thứ này thường được đọc cùng lúc (khi hiển thị hồ sơ khách hàng)
- Family `orders` chứa các cột: `ODR1001`, `ODR1002`, `ODR1003`, `ODR1004` (mỗi đơn hàng là 1 cột riêng) — vì đơn hàng ít khi cần đọc chung với profile

→ Ý tưởng cốt lõi: **thiết kế schema theo cách bạn sẽ TRUY VẤN dữ liệu**, không theo cách chuẩn hóa lý thuyết như RDBMS.

**Gốc gác:** năm 2008 Google công bố paper **Bigtable**, định nghĩa: *"BigTable = sparse, distributed, persistent, multi-dimensional sorted map indexed by (row_key, column_key, timestamp)"* — nghĩa là mỗi giá trị còn được đánh dấu theo **thời gian (timestamp)**, cho phép lưu nhiều phiên bản của cùng 1 giá trị theo thời gian (VD trong slide: cột `contents:html` của trang `com.ccn.www` có 3 phiên bản tại các thời điểm t2, t6, t8).

**Đại diện thật:** Google Bigtable (bản gốc, nội bộ Google), Apache Cassandra, Apache HBase (chạy trên Hadoop), Hypertable, Accumulo.

**Ứng dụng thực tế điển hình:** dữ liệu time-series (log theo thời gian), hệ thống ghi nhiều/đọc nhiều với khối lượng cực lớn (Facebook dùng HBase cho email/tin nhắn/SMS — nói kỹ ở phần 5).

### 4.4. Graph Databases — phức tạp nhất, mạnh nhất về quan hệ
**Bản chất:** lưu trực tiếp **thực thể (node)** và **quan hệ (edge/relationship)** giữa chúng, thay vì tính toán quan hệ qua JOIN như RDBMS.
- **Node** = 1 đối tượng cụ thể, có **thuộc tính (properties)**, ví dụ `name`.
- **Edge** = có **hướng (directional)** và có **loại (type)**, ví dụ `likes`, `friend`, `employee`, `author`, `category`.

Ví dụ thật từ slide (đồ thị người + công ty + sách):
- `Anna` --employee--> `BigCo`
- `Barbara` --friend--> `Anna`, `Barbara` --employee--> `BigCo`
- `Carol` --friend--> `Barbara`, `Carol` --likes--> `NoSQL Distilled`
- `Pramod` --author--> `NoSQL Distilled`, cuốn sách này thuộc `category` `Databases`

→ Truy vấn tự nhiên kiểu: *"Tìm tất cả node vừa là 'employee' của BigCo, vừa 'likes' cuốn NoSQL Distilled"* — đây chính là kiểu câu hỏi mà Graph DB trả lời cực nhanh, còn RDBMS thì phải JOIN rất nhiều bảng mới ra được.

**Vì sao không dùng RDBMS cho bài toán này luôn?**
- Nếu lưu quan hệ dạng graph trong RDBMS, bạn thường chỉ tối ưu được cho **1 kiểu quan hệ cố định** (VD: "ai là quản lý của tôi").
- Muốn thêm 1 loại quan hệ mới → phải sửa schema rất nhiều.
- RDBMS buộc bạn phải **thiết kế trước** dựa theo kiểu truy vấn (traversal) bạn định làm; nếu sau này truy vấn thay đổi, dữ liệu phải tổ chức lại.
- Trong khi đó, Graph DB **lưu sẵn (persisted)** quan hệ dưới dạng cạnh — không cần tính toán lại (calculated) mỗi lần truy vấn, nên duyệt qua nhiều tầng quan hệ (VD: bạn của bạn của bạn) nhanh hơn nhiều.

**Đại diện thật:** Neo4j (phổ biến nhất), OrientDB, Apache Giraph, Titan, InfiniteGraph.

**Ứng dụng thực tế điển hình:** mạng xã hội (bạn bè, follow), hệ thống gợi ý (recommendation), phát hiện gian lận (fraud detection — lần theo chuỗi giao dịch bất thường), quản lý tri thức (knowledge graph).

---

## 5. Case study thật: Facebook dùng công nghệ gì

Số liệu Facebook (2016) trong slide:
- 1.86 tỷ người dùng hoạt động hàng tháng
- 4 triệu lượt "like" mỗi phút
- 250 tỷ ảnh được lưu (350 triệu ảnh upload mỗi ngày)
- 300 PB dữ liệu người dùng (2014)
- Số server: 2009 có 10.000 server → 2010: 30.000 → 2012: ước tính 180.000 server

**Công nghệ NoSQL/Big Data đứng sau Facebook (theo slide, có nguồn):**
| Công nghệ | Loại | Dùng để làm gì |
|---|---|---|
| **Apache Hadoop (HDFS + MapReduce)** | Distributed file system + xử lý phân tán | HDFS lưu hơn 100 PB trong 1 cluster; MapReduce tính toán trên khối lượng dữ liệu khổng lồ |
| **Apache Hive** | SQL-like layer trên Hadoop | Cho phép truy vấn kiểu SQL trên dữ liệu lưu ở HDFS, tích hợp đánh giá qua MapReduce |
| **Apache HBase** | Column-family DB (chạy trên Hadoop) | Dùng cho email, chat, SMS — từng thay thế MySQL và Cassandra cho việc này |
| **Memcached** | Distributed key-value store | Làm lớp cache giữa web server và MySQL server (thời kỳ đầu của Facebook) |
| **Apache Giraph** | Graph database | Xử lý đồ thị "bạn bè" khổng lồ của Facebook — dùng từ 2013 cho các tác vụ phân tích tới hàng nghìn tỷ cạnh (trillion edges) |
| **RocksDB** | High-performance key-value store | Phát triển nội bộ tại Facebook, sau đó mở mã nguồn |

→ Bài học rút ra: **Facebook không dùng 1 loại DB cho tất cả** — đây chính là ví dụ sống động nhất cho khái niệm **Polyglot persistence** đã nói ở mục 3.5: mỗi loại dữ liệu (ảnh, tin nhắn, quan hệ bạn bè, cache tạm...) được giao cho đúng loại DB phù hợp nhất với nó.

---

## 6. Tóm tắt siêu ngắn để ôn nhanh trước khi vào lớp / thi

- **Big Data (3V)** làm RDBMS đuối sức vì: schema cứng, chuẩn hóa gây JOIN nhiều, ACID đầy đủ chậm khi phân tán.
- **NoSQL** đánh đổi: bớt chặt ACID (chuyển sang eventually consistent), bỏ schema cứng, đổi lấy scale ngang + đọc nhanh + rẻ.
- **4 loại NoSQL, nhớ theo độ phức tạp tăng dần:**
  - Key-Value: chỉ `put/get/delete` theo khóa → Redis, DynamoDB
  - Document: key-value nhưng value là JSON có thể truy vấn theo field → MongoDB
  - Column-family: row có nhiều cột, nhóm theo column family hay dùng chung → Cassandra, HBase, (gốc: Google Bigtable)
  - Graph: lưu trực tiếp node + edge có hướng, có loại → Neo4j
- **RDBMS không chết** — cả 2 hướng đang giao thoa (**Polyglot persistence** là từ khóa quan trọng nhất của cả bài): dùng đúng DB cho đúng bài toán, trong cùng 1 hệ thống lớn.

---

## Nguồn tham khảo (lấy nguyên văn từ slide gốc, để tra cứu thêm nếu cần)
- I. Holubová, J. Kosek, K. Minařík, D. Novák. *Big Data a NoSQL databáze*. Praha: Grada Publishing, 2015.
- Sadalage, P. J., & Fowler, M. (2012). *NoSQL Distilled: A Brief Guide to the Emerging World of Polyglot Persistence*. Addison-Wesley Professional.
- Chang, F. et al. (2008). *Bigtable: A Distributed Storage System for Structured Data*. ACM TOCS, 26(2), pp 1–26.
- Dean, J. & Ghemawat, S. (2004). *MapReduce: Simplified Data Processing on Large Clusters*.
- db-engines.com/en/ranking (bảng xếp hạng các DB theo mức phổ biến, cập nhật liên tục)
- nosql-database.org
