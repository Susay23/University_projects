# Ghi chép: NoSQL Databases (CT113H) — Lecture 2: Distributed Computing with MapReduce
**GV: N.C. Danh — Khoa Công nghệ phần mềm, Trường CNTT&TT, ĐH Cần Thơ**
**Ghi chép ngày: 14/09/2026 — tổng hợp toàn bộ 57 slide**

---

## 0. Bức tranh tổng thể trước khi đi vào chi tiết

Bài này trả lời câu hỏi: **"Khi dữ liệu quá lớn để 1 máy xử lý, làm sao chia việc ra cho nhiều máy mà vẫn ra đúng 1 kết quả, và làm sao chịu được lỗi khi có máy chết giữa đường?"**

Mạch bài:
1. Đặt vấn đề: xử lý tập trung (centralized) không còn ổn với Big Data →
2. Google gặp đúng vấn đề này năm 2003 (xếp hạng hàng chục tỷ trang web) → tự chế ra **GFS** (chỗ lưu) + **MapReduce** (cách xử lý) →
3. MapReduce là 1 **mô hình lập trình** rất đơn giản: bạn chỉ viết 2 hàm `map` và `reduce`, phần còn lại (phân tán, gộp nhóm, chịu lỗi) framework tự lo →
4. **Apache Hadoop** là bản mã nguồn mở tái tạo lại ý tưởng GFS + MapReduce của Google, gồm HDFS (file system) + Hadoop MapReduce (xử lý) →
5. Ngày nay có nhiều hệ thống khác cũng cài đặt/hỗ trợ ý tưởng MapReduce: Spark, Amazon EMR, cả MongoDB.

Nắm chắc mạch này rồi thì phần chi tiết dưới đây chỉ là "đổ đầy" vào khung sẵn có.

---

## 1. Đặt vấn đề: Distributed Data Processing

Câu hỏi mở đầu của slide: **"Cách xử lý phân tán tốt nhất là gì?"** → Trả lời ngắn gọn: **"Tập trung (và xử lý trong RAM)? Đừng làm vậy nếu không buộc phải làm."** — ý muốn nói: xử lý tập trung 1 máy chỉ nên dùng khi dữ liệu còn nhỏ; với Big Data thì bắt buộc phải phân tán.

### 1.1. Vì sao phải phân tán
- Big Data analytics cần xử lý khối lượng dữ liệu lớn **nhanh**.
- Muốn dùng **cụm máy thường (computing cluster)** thay vì 1 siêu máy tính (super-computer) — rẻ hơn, dễ mở rộng hơn.
- Nhưng: **truyền dữ liệu (gửi data) giữa các node tính toán là rất tốn kém.**
→ Từ đó sinh ra nguyên lý cốt lõi của cả Big Data: **"đưa việc tính toán đến gần dữ liệu"** (moving the computing to data) — thay vì kéo dữ liệu về 1 chỗ để tính, ta đưa code đến nơi dữ liệu đang nằm sẵn rồi tính tại chỗ.

### 1.2. Kiến trúc cụm máy tính thực tế (theo Leskovec, Rajaraman, Ullman — *Mining of Massive Datasets*, 2014)
Một cụm máy chủ thực tế được tổ chức thành nhiều **rack (kệ máy chủ)**, các rack nối với nhau qua switch trung tâm, mỗi rack chứa nhiều **compute node**.

Vì phần cứng **hỏng là chuyện thường xảy ra, không phải ngoại lệ** (HW failures are rather rule than exception) trong 1 cụm máy có hàng nghìn node, nên hệ thống phải thiết kế theo 2 nguyên tắc sống còn:
1. **File phải được lưu dư thừa (redundantly)** — và phải lưu trên **các rack khác nhau**, để nếu 1 rack chết (mất điện, đứt switch) thì rack khác vẫn còn bản sao.
2. **Việc tính toán phải được chia thành các task độc lập** — để nếu 1 task chết giữa đường, chỉ cần chạy lại đúng task đó, không cần chạy lại từ đầu toàn bộ công việc.

→ Đây chính là 2 nguyên lý mà cả GFS và MapReduce sẽ áp dụng ngay sau đây.

---

## 2. Google MapReduce — nơi mọi thứ bắt đầu

### 2.1. Bài toán gốc: PageRank
**PageRank** là thuật toán xếp hạng trang web dựa trên số lượng và chất lượng các liên kết trỏ đến trang đó — giả định: trang quan trọng thì được nhiều trang khác (đặc biệt là các trang cũng quan trọng) trỏ link đến. (nguồn: Wikipedia — en.wikipedia.org/wiki/PageRank).

### 2.2. Vấn đề của Google năm 2003
1. Làm sao xếp hạng **hàng chục tỷ trang web** theo độ quan trọng (PageRank) trong thời gian "chấp nhận được"?
2. Làm sao tính hiệu quả khi dữ liệu **nằm rải rác trên hàng nghìn máy tính**?

Thêm 2 đặc điểm quan trọng của dữ liệu lúc đó:
- Mỗi file dữ liệu riêng lẻ có thể **cực lớn** (cỡ terabyte hoặc hơn).
- File **ít khi bị sửa** — việc tính toán chủ yếu là **đọc nhiều, ghi ít** (read-heavy, not write-heavy); nếu có ghi thì chỉ **ghi thêm vào cuối file** (append), không sửa giữa file.

→ Chính 2 đặc điểm này quyết định toàn bộ thiết kế của GFS phía dưới (write-once/read-many, ghi bằng cách append).

### 2.3. Giải pháp của Google: 2 thành phần
1. **Google File System (GFS)** — 1 hệ thống file phân tán (chỗ lưu).
2. **MapReduce** — 1 mô hình lập trình cho xử lý dữ liệu phân tán (cách xử lý).

### 2.4. Google File System (GFS) — chi tiết
- File được chia thành các **chunk** (khối), kích thước thường là **64 MB**.
- Mỗi chunk được **nhân bản (replicate) tại 3 máy khác nhau**, theo cách "thông minh" — ví dụ **không bao giờ để cả 3 bản trên cùng 1 rack** (để nếu rack đó chết thì vẫn còn bản ở rack khác).
- Kích thước chunk và số lượng bản sao (replication factor) đều **có thể tùy chỉnh (tunable)**.
- Kiến trúc: **1 máy làm master, các máy còn lại làm chunkserver.**
  - **Master** giữ toàn bộ **metadata** của hệ thống file: bản đồ (mapping) từ file → chunk và vị trí (location) của các chunk đó.
  - Khi client muốn đọc 1 file: **client hỏi master trước** ("chunk này ở đâu?") → **rồi mới liên hệ trực tiếp với chunkserver** tương ứng để lấy dữ liệu thật.
  - Metadata của master **cũng được nhân bản** — để nếu master chết thì không mất luôn "bản đồ" của cả hệ thống.

**Sơ đồ GFS Architecture** (nguồn: Ghemawat, Gobioff, Leung — bài báo GFS gốc, ACM, dl.acm.org/citation.cfm?id=945450), diễn giải lại luồng hoạt động:
1. Application gửi yêu cầu qua **GFS client**.
2. GFS client hỏi **GFS master**: "cho tôi (tên file, chỉ số chunk)".
3. Master trả về: **(chunk handle, danh sách vị trí các chunk)** — đây là các *thông điệp điều khiển (control message)*, đường mũi tên mảnh trong sơ đồ.
4. Client cầm chunk handle này, **liên hệ trực tiếp** với 1 GFS chunkserver để lấy **(chunk handle, byte range)** → nhận về **chunk data** thật — đây là *thông điệp dữ liệu (data message)*, đường mũi tên đậm trong sơ đồ.
→ Điểm mấu chốt cần nhớ: **dữ liệu thật không đi qua master** — master chỉ đóng vai trò "tổng đài" chỉ đường, còn dữ liệu thật đi thẳng giữa client và chunkserver. Đây là lý do master không bị nghẽn cổ chai (bottleneck) dù có hàng nghìn client cùng đọc dữ liệu.

---

## 3. MapReduce — cơ chế lập trình cốt lõi

### 3.1. Ý tưởng chung
- MapReduce là 1 mô hình lập trình **nằm phía trên** 1 hệ thống file phân tán (như GFS/HDFS).
- Ban đầu: **không có data model** — dữ liệu được lưu trực tiếp trong file thô, không có khái niệm bảng/document như các NoSQL DB học ở bài trước.
- 1 tác vụ tính toán phân tán có **3 giai đoạn**:
  1. **Map phase** — biến đổi dữ liệu (data transformation)
  2. **Grouping phase** — nhóm dữ liệu theo khóa (làm **tự động** bởi framework, người dùng không cần viết code cho bước này)
  3. **Reduce phase** — tổng hợp dữ liệu (data aggregation)
- **Người dùng chỉ cần định nghĩa 2 hàm: `map` và `reduce`.** Đây chính là điểm khiến MapReduce trở nên đơn giản và mạnh mẽ — bạn không cần biết gì về phân tán, chỉ cần biết cách biến đổi 1 dòng dữ liệu (map) và cách gộp nhiều giá trị lại (reduce).

### 3.2. Hàm Map — chi tiết
- **Input:** 1 mẩu dữ liệu đơn lẻ (ví dụ: 1 dòng text) từ 1 file dữ liệu.
- **Output:** **0 hoặc nhiều cặp (key, value)**.
- Điểm đặc biệt: các "key" ở đây **không giống khóa chính trong DB** — chúng **không cần là duy nhất (unique)**. 1 lần chạy map trên 1 input còn có thể sinh ra **nhiều cặp key-value có cùng key**.
- Map phase = áp dụng hàm map lên **tất cả** các item đầu vào.

**Minh họa (theo sơ đồ slide):** dữ liệu đầu vào là 1 dãy ô vuông trắng (chưa có gì). Sau khi qua map function, mỗi ô sinh ra 1 hoặc vài "chấm tròn" có **màu khác nhau** — mỗi màu đại diện cho 1 key khác nhau. Vậy: input → map → output rải rác, có màu (= có key) nhưng chưa được sắp xếp gì cả.

### 3.3. Grouping Phase (Shuffle/Shuffling) — chi tiết
- Đây là bước **gộp nhóm (nhào trộn)**: tất cả cặp key-value sinh ra từ Map phase được **nhóm lại theo key**.
- Các value có **cùng key** sẽ được gửi đến **cùng 1 reducer**.
- Các value đó được **hợp nhất thành 1 danh sách duy nhất (key, list)** — dạng dữ liệu này rất thuận tiện cho hàm reduce xử lý tiếp.
- **Bước này do framework MapReduce tự thực hiện — người dùng không cần viết code.**

**Minh họa:** các chấm tròn màu khác nhau (đang nằm rải rác từ bước Map) được "gom" lại thành 3 hộp riêng — 1 hộp toàn chấm đen, 1 hộp toàn chấm xám, 1 hộp toàn chấm trắng. Đây chính là ý nghĩa của "Shuffle (grouping) phase": không tạo dữ liệu mới, chỉ **sắp xếp lại theo màu (key)**.

### 3.4. Reduce Phase — chi tiết
- **Reduce:** kết hợp (combine) các value của từng key để ra **kết quả cuối cùng**.
- **Input:** (key, value-list) — value-list chứa **toàn bộ** giá trị được sinh ra cho key đó trong Map phase.
- **Output:** (key, value-list) — có thể là **0 hoặc nhiều bản ghi kết quả**.

### 3.5. Sơ đồ tổng hợp toàn bộ pipeline (rất quan trọng — nên vẽ lại tay 1 lần cho nhớ)
Toàn bộ luồng theo đúng thứ tự, minh họa bằng chấm tròn màu trong slide:
```
input data  (các ô trắng chưa xử lý)
    ↓  map function
intermediate output  (chấm tròn màu rải rác — mỗi màu = 1 key)
    ↓  shuffle (grouping) phase
input data  (đã gom theo màu: hộp đen | hộp xám | hộp trắng)
    ↓  reduce function
output data  (mỗi hộp màu → 1 kết quả tổng hợp)
```
→ Đây là "khung xương" của MỌI bài toán MapReduce — dù bài toán khác nhau (đếm từ, tính PageRank, gộp link...), nó luôn chạy đúng 5 bước này.

### 3.6. Ví dụ 1: Word Count (đếm từ) — ví dụ kinh điển nhất của MapReduce
**Đề bài:** tính tần suất xuất hiện của mỗi từ trong 1 tập văn bản.

Pseudocode (nguyên văn từ slide):
```
map(String key, Text value):
  // key: tên document (bị bỏ qua, không dùng)
  // value: nội dung document (các từ)
foreach word w in value:
    emitIntermediate(w, 1);

reduce(String key, Iterator values):
  // key: 1 từ
  // values: danh sách các số đếm
int result = 0;
foreach v in values:
    result += v;
emit(key, result);
```
→ Giải thích bằng lời: hàm `map` đọc từng document, gặp từ nào thì "phát" ra cặp `(từ đó, 1)` — nghĩa là "tôi thấy từ này 1 lần". Hàm `reduce` nhận về **toàn bộ danh sách số 1** đã gom theo từng từ, rồi **cộng dồn lại** ra tổng số lần xuất hiện.

**Sơ đồ trực quan đầy đủ** (nguồn: cs.uml.edu/~jlu1/doc/source/report/MapReduce.html), với input là 3 dòng text:
```
Deer Bear River
Car Car River
Deer Car Bear
```
Luồng xử lý qua 6 bước: **Input → Splitting → Mapping → Shuffling → Reducing → Final result**
1. **Splitting:** 3 dòng được chia thành 3 phần riêng (mỗi worker nhận 1 dòng).
2. **Mapping:** mỗi dòng sinh ra các cặp `(từ, 1)` — VD dòng "Deer Bear River" → `(Deer,1) (Bear,1) (River,1)`.
3. **Shuffling:** tất cả cặp có cùng từ được gom lại — VD tất cả `(Bear,1)` từ mọi dòng được gom vào 1 nhóm.
4. **Reducing:** cộng các số 1 trong từng nhóm — `Bear: 1+1=2`, `Car: 1+1+1=3`, `Deer: 1+1=2`, `River: 1+1=2`.
5. **Final result:** `{Bear:2, Car:3, Deer:2, River:2}`.

### 3.7. Combiner — "tối ưu hóa" trước khi Shuffle
- Điều kiện áp dụng: nếu hàm reduce có tính chất **giao hoán (commutative) và kết hợp (associative)** — nghĩa là thứ tự cộng dồn không ảnh hưởng đến kết quả (VD: đếm tổng — cộng theo thứ tự nào cũng ra cùng kết quả).
- Khi đó, ta có thể **gộp giá trị theo từng phần (per partes) ngay tại chỗ**, trước khi gửi đi.
- **Combiner** = bước (tùy chọn) áp dụng **lại chính hàm reduce** ngay sau Map phase, **trước khi shuffle và phân phối tới các reducer node** — mục đích là **giảm khối lượng dữ liệu phải truyền qua mạng**.
- **Lưu ý quan trọng:** dù có combiner, **vẫn phải chạy Reduce phase đầy đủ** ở cuối — combiner chỉ là bước "rút gọn cục bộ" (partial reduction), không thay thế Reduce.

**Ví dụ Word Count có Combiner:**
```
combine(String key, Iterator values):
  // key: 1 từ
  // values: danh sách số đếm cục bộ (local counts)
int result = 0;
foreach v in values:
    result += v;
emit(key, result);
```
→ Code combiner **giống hệt** code reduce — vì bài Word Count thỏa điều kiện commutative/associative.

**Sơ đồ minh họa** (nguồn: admin-magazine.com/HPC/Articles/MapReduce-and-Hadoop): dữ liệu chia thành `Block 1`, `Block 2` → mỗi block qua 1 **Mapper** riêng sinh cặp (chữ, 1) → mỗi Mapper có 1 **Combiner** riêng cộng dồn cục bộ ngay tại đó (VD Block 1 có 2 cặp `(B,1)` → Combiner gộp thành `(B,2)` **trước khi** gửi đi) → sau đó mới **Shuffle** để gom theo key thật trên toàn hệ thống → cuối cùng **Reducer** cộng tổng ra kết quả cuối `(A,2) (B,3) (C,2) (D,4) (E,1)`.

→ **Bài học thực tế cực quan trọng:** Combiner giúp giảm đáng kể lượng dữ liệu phải gửi qua mạng giữa các máy (network I/O) — vì thay vì gửi 5-6 cặp `(B,1)` riêng lẻ từ 1 block, ta chỉ gửi 1 cặp `(B,2)` đã cộng sẵn. Đây là lý do Combiner luôn được khuyến nghị dùng khi bài toán cho phép (như đếm tổng, tìm max/min).

### 3.8. MapReduce Framework — framework lo những gì?
Framework tự động xử lý:
- Phân tán và chạy song song (parallelizing) việc tính toán
- Giám sát (monitoring) toàn bộ tác vụ phân tán
- Grouping phase (gộp các kết quả trung gian lại)
- **Tự phục hồi khi có lỗi (recovering from failures)**

→ Người dùng **chỉ cần viết map & reduce**, nhưng cũng có thể định nghĩa thêm 1 số hàm phụ khác (xem mục dưới).

**Sơ đồ kiến trúc gốc** (nguồn: Dean, J. & Ghemawat, S. (2004). *MapReduce: Simplified Data Processing on Large Clusters*, OSDI 2004 — đây chính là bài báo khai sinh ra MapReduce), diễn giải luồng hoạt động:
1. **User Program** "fork" (tạo tiến trình) ra 1 **Master** và nhiều **worker**.
2. Master **"assign map"** — giao việc map cho các worker rảnh, dựa trên các **split** (mảnh dữ liệu đầu vào, VD split 0-4).
3. Mỗi worker làm map: **(3) read** dữ liệu từ split được giao → **(4) local write** — ghi **kết quả trung gian ra đĩa cục bộ** (local disk), không ghi qua mạng.
4. Master **"assign reduce"** — giao việc reduce cho worker khác.
5. Worker reduce thực hiện **(5) remote read** — đọc kết quả trung gian **từ xa** (từ đĩa của các worker map) về.
6. Worker reduce **(6) write** kết quả cuối cùng ra **output file**.
→ Điểm hay: kết quả trung gian **ghi ra đĩa cục bộ trước**, chỉ khi cần mới đọc từ xa — giúp giảm tải mạng và cho phép **restart lại đúng phần bị lỗi** mà không ảnh hưởng phần khác.

### 3.9. MapReduce Framework — 7 thành phần chi tiết (rất hay bị hỏi trong đề thi)
1. **Input reader** (hàm) — định nghĩa cách đọc dữ liệu từ nơi lưu trữ bên dưới.
2. **Map** (giai đoạn):
   - Master node chuẩn bị **M mảnh dữ liệu (data split)** và **M task Map** đang chờ (idle).
   - Từng split được giao cho 1 Map task chạy trên 1 worker.
   - Khi 1 task xong, **kết quả trung gian được lưu lại**.
3. **Combiner** (hàm, tùy chọn) — gộp kết quả trung gian cục bộ ngay tại Map phase (như mục 3.7).
4. **Partition** (hàm) — quyết định cách **chia kết quả trung gian ra cho từng Reducer** (từng Reducer nhận phần nào).
5. **Comparator** (hàm) — sắp xếp và nhóm (sort & group) input cho mỗi Reducer.
6. **Reduce** (giai đoạn):
   - Master node tạo **R task Reduce** đang chờ trên các worker.
   - Hàm Partition ở bước 4 quyết định **batch dữ liệu** nào thuộc về reducer nào.
   - Mỗi Reduce task dùng Comparator để tạo ra các cặp key-value đã sắp xếp.
   - Hàm Reduce được áp dụng trên mỗi cặp (key, value-list) đó.
7. **Output writer** (hàm) — định nghĩa cách ghi các cặp key-value kết quả ra ngoài.

→ Ghi nhớ nhanh: **map → (combine) → partition → comparator (sort/group) → reduce**. Người dùng bắt buộc viết `map` và `reduce`; các hàm còn lại (input reader, combiner, partition, comparator, output writer) là **tùy chọn/có sẵn mặc định** trong framework, chỉ cần override khi có nhu cầu đặc biệt.

### 3.10. Ví dụ 2: Xây đồ thị backlink của các trang web
**Đề bài:** với mỗi trang, tìm những trang nào **trỏ link đến nó** (backlinks) — dữ liệu chuẩn bị cho thuật toán PageRank đã nói ở đầu bài.

```
map(String url, Text html):
  // url: địa chỉ trang web
  // html: nội dung HTML (các tag đã được duyệt tuyến tính)
foreach tag t in html:
    if t is <a> then:
        emitIntermediate(t.href, url);

reduce(String key, Iterator values):
  // key: URL đích (target URL)
  // values: danh sách URL nguồn (source URL) trỏ đến nó
emit(key, values);
```
→ Ý tưởng: khi map quét thấy `<a href="X">` trong trang `url`, nó phát ra cặp `(X, url)` — nghĩa là "trang X được trang `url` trỏ đến". Sau khi shuffle gom theo key (= URL đích), reduce chỉ cần **liệt kê lại toàn bộ danh sách value** — không cần tính toán gì thêm, vì bản chất bài toán chỉ là "gom nhóm".

**Ví dụ chạy tay cụ thể (nguyên văn từ slide) — rất hữu ích để hiểu rõ luồng dữ liệu qua từng bước:**

Input (3 trang):
```
("http://cnn.com",   "<html>...<a href="http://cnn.com">link</a>...</html>")
("http://ihned.cz",  "<html>...<a href="http://cnn.com">link</a>...</html>")
("http://idnes.cz",  "<html>...<a href="http://cnn.com">x</a>...
                            <a href="http://ihned.cz">y</a>...<a href="http://idnes.cz">z</a></html>")
```

Sau Map phase (mỗi thẻ `<a>` sinh ra 1 cặp (URL đích, URL nguồn)):
```
("http://cnn.com",   "http://cnn.com")
("http://cnn.com",   "http://ihned.cz")
("http://cnn.com",   "http://idnes.cz")
("http://ihned.cz",  "http://idnes.cz")
("http://idnes.cz",  "http://idnes.cz")
```

Sau Shuffle + Reduce phase (gom theo URL đích thành danh sách):
```
("http://cnn.com",  ["http://cnn.com", "http://ihned.cz", "http://idnes.cz"])
("http://ihned.cz", ["http://idnes.cz"])
("http://idnes.cz", ["http://idnes.cz"])
```
→ Đọc kết quả: `cnn.com` được **cả 3 trang** trỏ đến (kể cả chính nó), `ihned.cz` chỉ được `idnes.cz` trỏ đến. Đây chính là dữ liệu đầu vào cho bước tính PageRank thật (không nằm trong phạm vi slide này).

### 3.11. Ví dụ 3: Đếm số từ theo độ dài
**Đề bài:** trong văn bản, có bao nhiêu từ ứng với mỗi độ dài (1 chữ, 2 chữ, 3 chữ...)?
```
map(String key, Text value):
foreach word w in value:
    emitIntermediate(length(w), 1);

reduce(Integer key, Iterator values):
  // key: 1 độ dài
  // values: danh sách số đếm
int result = 0;
foreach v in values:
    result += v;
emit(key, result);
```
→ Cấu trúc **giống hệt Word Count**, chỉ khác: key không phải "từ" mà là "độ dài của từ" (`length(w)`). Đây là minh chứng rất rõ: **rất nhiều bài toán MapReduce chỉ khác nhau ở cách bạn chọn "key" là gì** — bản chất thuật toán y hệt nhau.

### 3.12. Đặc điểm (Features) của MapReduce
- Dùng kiến trúc **"shared nothing"** — các node hoạt động **độc lập, không chia sẻ RAM/đĩa** với nhau. Đây cũng là đặc điểm chung của **rất nhiều hệ NoSQL** (đã học ở Lecture 1) — không phải chỉ riêng MapReduce.
- Dữ liệu được **phân chia (partition) và nhân bản (replicate)** trên nhiều node:
  - **Ưu điểm:** số lượng request đọc/ghi mỗi giây (throughput) rất lớn.
  - **Nhược điểm:** phát sinh **bài toán điều phối (coordination problem)** — phải luôn biết node nào đang giữ dữ liệu nào, và tại thời điểm nào (vì dữ liệu có thể đang được cập nhật/di chuyển).

### 3.13. MapReduce áp dụng được khi nào, và giới hạn của nó
- MapReduce **áp dụng được** nếu bài toán **có thể chia nhỏ chạy song song (parallelizable)**.
- Nhưng có **2 vấn đề lớn**:
  1. **Mô hình lập trình bị giới hạn** — chỉ có đúng 2 giai đoạn theo 1 khuôn cố định (map rồi reduce) — không phải bài toán nào cũng ép được vào khuôn này dễ dàng.
  2. **Không có data model** — MapReduce chỉ làm việc trên **"khối dữ liệu thô" (data chunks)**, không hiểu gì về cấu trúc bảng/document/quan hệ.
- **Câu trả lời của Google cho vấn đề số 2 chính là BigTable** — hệ **column-family đầu tiên (2005)** đã học ở Lecture 1! Các hệ sau này đi theo hướng này: **HBase** (chạy trên Hadoop), **Cassandra**...

→ Đây là điểm nối rất quan trọng giữa 2 bài giảng: **MapReduce lo phần "xử lý"**, còn **BigTable/HBase/Cassandra lo phần "lưu trữ có cấu trúc"** — 2 mảnh ghép bổ sung cho nhau, không thay thế nhau.

---

## 4. Apache Hadoop — bản mã nguồn mở của ý tưởng Google

### 4.1. Giới thiệu chung
- **Framework mã nguồn mở**, viết bằng **Java**.
- Có thể chạy ứng dụng trên **cụm phần cứng phổ thông (commodity hardware)** quy mô lớn: tập dữ liệu nhiều terabyte, hàng nghìn node.
- **Bắt nguồn trực tiếp từ ý tưởng GFS + MapReduce của Google** — nói cách khác, Hadoop chính là "phiên bản mở" mà cả thế giới (ngoài Google) có thể dùng được. (web: hadoop.apache.org)

### 4.2. 4 module chính của Hadoop
1. **Hadoop Common** — các hàm hỗ trợ chung cho những module khác.
2. **HDFS (Hadoop Distributed File System)** — hệ thống file phân tán, cho phép **truy cập dữ liệu ứng dụng với throughput cao**.
3. **Hadoop YARN** — lo việc **lập lịch công việc (job scheduling)** và **quản lý tài nguyên cụm (cluster resource management)**.
4. **Hadoop MapReduce** — hệ thống xử lý dữ liệu song song, **chạy dựa trên YARN**.

**Sơ đồ phân lớp** (nguồn: goo.gl/NPuuJr) — nhớ theo đúng thứ tự từ dưới lên:
```
┌─────────────────┬─────────────────┐
│ MapReduce        │ Others           │   ← lớp xử lý dữ liệu (data processing)
│ (data processing) │ (data processing)│
├─────────────────┴─────────────────┤
│           YARN                     │   ← lớp quản lý tài nguyên cụm
│      (cluster resource management) │
├─────────────────────────────────────┤
│            HDFS                     │   ← lớp lưu trữ (bền, dư thừa)
│     (redundant, reliable storage)   │
└─────────────────────────────────────┘
```
→ Đây chính là câu trả lời cho câu hỏi "HDFS, YARN, MapReduce liên hệ nhau thế nào": **HDFS lưu trữ ở đáy → YARN quản lý tài nguyên ở giữa → MapReduce (hoặc công cụ khác như Spark) chạy xử lý ở trên cùng, dùng chung tài nguyên do YARN cấp phát.**

### 4.3. HDFS — chi tiết
**Đặc điểm chung:**
- Miễn phí, mã nguồn mở.
- Đa nền tảng (pure Java) — có binding cho các ngôn ngữ khác ngoài Java.
- **Khả năng mở rộng cao (highly scalable).**
- **Chịu lỗi tốt (fault-tolerant)** — theo đúng nguyên lý đã nói ở mục 1.2: "lỗi là chuyện thường (failure is the norm rather than exception)", vì 1 instance HDFS có thể gồm hàng nghìn máy và bất kỳ máy nào cũng có thể hỏng → HDFS có khả năng **phát hiện lỗi** và **tự phục hồi nhanh, tự động**.
- **Không tối ưu nhất về hiệu năng (not the best in efficiency)** — đánh đổi hiệu năng thô để lấy độ tin cậy và khả năng mở rộng.

**Giả định về đặc tính dữ liệu (Data Characteristics) mà HDFS được thiết kế cho:**
- Truy cập kiểu **streaming** — đọc file từ đầu đến cuối, không nhảy cóc random.
- **Batch processing**, không phải truy cập tương tác trực tiếp của người dùng (interactive).
- Tập dữ liệu và file **kích thước lớn**.
- **Write-once / read-many** — 1 file, sau khi tạo, **hiếm khi bị sửa lại** → giả định này giúp đơn giản hóa rất nhiều vấn đề đồng bộ (coherency).
- Ứng dụng phù hợp nhất với mô hình này: **MapReduce, web-crawler, data warehouse...**

**Kiến trúc cơ bản (Basic Components):**
- Mô hình **Master/Slave**.
- File được **chia thành các block** (mặc định **128 MB**, có thể cấu hình theo từng file).
- **NameNode** (máy chủ chính — master):
  - Quản lý **namespace của hệ thống file** (mở/đóng/đổi tên file và thư mục, điều chỉnh quyền truy cập).
  - Xác định **mapping từ block → DataNode nào đang giữ block đó**.
- **DataNode** (quản lý các block file thật):
  - Thực hiện đọc/ghi/tạo/xóa/nhân bản block.
  - Thường **1 DataNode chạy trên 1 máy vật lý**.

**Sơ đồ HDFS Architecture** — luồng hoạt động:
1. **Client** gửi **Metadata ops** (VD: "file này ở đâu?") đến **NameNode**.
2. NameNode trả lời dựa trên **Metadata** đã lưu (dạng: `/home/foo/data, 3, ...` — tên file, số bản sao...).
3. Client sau đó thực hiện **Read/Write trực tiếp với DataNode** (không qua NameNode nữa) — DataNode nằm rải trên nhiều **Rack** khác nhau (VD Rack 1, Rack 2 trong sơ đồ).
4. Các **Block** trên DataNode được **Replication** (nhân bản) sang DataNode ở rack khác — y hệt tinh thần "không để tất cả bản sao trên cùng 1 rack" của GFS đã học ở mục 2.4.
→ **Nhận xét:** cấu trúc NameNode/DataNode của HDFS **gần như là bản sao 1-1** của Master/Chunkserver trong GFS — chỉ đổi tên gọi.

**NameNode — 2 cấu trúc dữ liệu quan trọng cần nhớ:**
- **FsImage** — chứa **toàn bộ namespace hệ thống file** + mapping block→file + các thuộc tính hệ thống file. Được thiết kế **compact (gọn)** để có thể **nạp hết vào RAM của NameNode** (chỉ cần khoảng 4 GB RAM là đủ cho FsImage).
- **EditLog** — 1 **transaction log**, ghi lại **mọi thay đổi** với metadata (VD: tạo file mới, đổi replication factor của 1 file...).

**DataNode:**
- Lưu dữ liệu dưới dạng **file trên hệ thống file cục bộ** của chính nó — **mỗi HDFS block là 1 file riêng**.
- DataNode **không biết gì về "HDFS file system"** ở tầng logic — nó chỉ biết mình đang giữ những block nào.
- Khi khởi động (startup): DataNode tự tạo ra **BlockReport** (danh sách toàn bộ block HDFS mà nó đang giữ) và **gửi báo cáo này lên NameNode**.

**Blocks & Replication:**
- HDFS lưu được file rất lớn nhờ chia thành nhiều block **cùng kích thước** (trừ block cuối cùng của file, thường nhỏ hơn).
- Kích thước block **cấu hình được theo từng file** (mặc định 128 MB).
- Block được **nhân bản để chịu lỗi**; số lượng bản sao (number of replicas) **cấu hình được theo từng file**.
- NameNode nhận **HeartBeat** (tín hiệu "tôi vẫn sống") và **BlockReport** (danh sách block) từ **mỗi DataNode** định kỳ.

**Sơ đồ Block Replication** minh họa: NameNode giữ bảng ánh xạ dạng `Filename, numReplicas, block-ids` (VD: `/users/sameerp/data/part-0, r:2, {1,3}` nghĩa là file `part-0` có 2 bản sao, gồm block 1 và block 3), còn các block thật (đánh số 1-5) được rải ra trên nhiều DataNode khác nhau, mỗi block xuất hiện ở ít nhất 2 DataNode khác nhau — đúng như số `numReplicas` NameNode đã ghi.

**Reliability (độ tin cậy):**
- Mục tiêu chính: lưu dữ liệu tin cậy dù xảy ra: NameNode chết, DataNode chết, hoặc **network partition** (1 nhóm DataNode bị mất kết nối với NameNode).
- Khi **không nhận được HeartBeat** từ 1 DataNode: NameNode **đánh dấu DataNode đó là "chết"** và **không gửi I/O request** đến nó nữa.
- Khi 1 DataNode "chết" → thường dẫn đến **tái nhân bản (re-replication)** — hệ thống tự động tạo thêm bản sao mới ở DataNode khác để đảm bảo đủ số lượng bản sao yêu cầu.

### 4.4. Hadoop MapReduce — chi tiết
- Yêu cầu:
  - 1 hệ thống file phân tán (thường là **HDFS**).
  - 1 engine phân tán/điều phối/giám sát/gom kết quả (thường là **YARN**).
- **2 thành phần chính** (trong mô hình Hadoop 1.x cổ điển — mô hình này về sau được YARN thay thế 1 phần, nhưng vẫn là kiến thức nền tảng cần biết):
  - **JobTracker** (master) = bộ lập lịch (scheduler) — theo dõi toàn bộ MapReduce job, **giao tiếp với HDFS NameNode để chạy task gần với nơi dữ liệu đang nằm** (đúng nguyên lý "moving computing to data" ở mục 1.1!).
  - **TaskTracker** (slave, trên mỗi node) — được giao 1 task Map hoặc Reduce (hoặc tác vụ khác) — **mỗi task chạy trong 1 JVM riêng của nó**.

**Sơ đồ Hadoop HDFS + MapReduce** (nguồn: bigdata.black/architecture/hadoop/what-is-hadoop) — cho thấy rõ **1 node vật lý gánh 2 vai trò cùng lúc**:
```
Name Node (Master Node)
  └── JobTracker
        │
   ┌────┴────┬─────────┬─────────┐
Slave Node  Slave Node  Slave Node  Slave Node
 TaskTracker  TaskTracker TaskTracker TaskTracker
 Data Node    Data Node   Data Node   Data Node
 Map│Reduce   Map│Reduce  Map│Reduce  Map│Reduce
```
→ Nhận xét quan trọng: **mỗi Slave Node vừa là DataNode (lưu dữ liệu HDFS) vừa là TaskTracker (chạy Map/Reduce)** — đây chính là cách hiện thực hóa nguyên lý "đưa việc tính toán đến gần dữ liệu": task Map được ưu tiên chạy ngay trên node đang giữ block dữ liệu đó, khỏi phải chuyển dữ liệu qua mạng.

**Sơ đồ Hadoop MapReduce: Schema** (theo giáo trình tiếng Séc của Holubová et al.) — luồng chi tiết hơn 1 bậc:
1. **Client** gửi **MapReduce job** đến **JobTracker**.
2. Input file trên **HDFS** được chia thành nhiều **part (phần)** (VD: part 1-5).
3. Mỗi part được 1 **TaskTracker** (vai Map) xử lý: đọc qua **Input Format** → chạy hàm **Map()** trong RAM → dùng **partition()/combine()** để chia kết quả trung gian ra các **region** (vùng, tương ứng với từng Reducer sẽ nhận).
4. Kết quả các region được gửi tới **TaskTracker (vai Reduce)** tương ứng: **read** → **sort** (dùng Comparator) → **reduce()** → **Output Format** → ghi ra **file kết quả trên HDFS**.
→ Sơ đồ này chính là bản minh họa trực quan cho **7 thành phần MapReduce Framework** đã nói ở mục 3.9 (Input reader, Map, Combiner, Partition, Comparator, Reduce, Output writer) — chỉ khác là gắn thêm tên thật của Hadoop (TaskTracker, JobTracker...).

### 4.5. Code thật: Hadoop WordCount bằng Java
**Lớp Map:**
```java
public class Map
      extends Mapper<LongWritable, Text, Text, IntWritable> {

    private final static IntWritable one = new IntWritable(1);
    private final Text word = new Text();

    @Override protected void map(LongWritable key, Text value,
        Context context) throws ... {
      String string = value.toString()
      StringTokenizer tokenizer = new StringTokenizer(string);
      while (tokenizer.hasMoreTokens()) {
        word.set(tokenizer.nextToken());
        context.write(word, one);
      }
    }
}
```
**Lớp Reduce:**
```java
public class Reduce
      extends Reducer<Text, IntWritable, Text, IntWritable> {

    @Override
    public void reduce (Text key, Iterable<IntWritable> values,
        Context context) throws ... {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      context.write(key, new IntWritable(sum));
    }
}
```
→ Đối chiếu với pseudocode Word Count ở mục 3.6: **`map()` tách chuỗi thành từng từ (`StringTokenizer`) và `context.write(word, one)` chính là `emitIntermediate(w, 1)`; `reduce()` cộng dồn `sum += val.get()` chính là `result += v`.** Cấu trúc pseudocode và code Java thật hoàn toàn tương ứng 1-1 — hiểu pseudocode là hiểu được code thật ngay.

### 4.6. Các dự án liên quan trong hệ sinh thái Hadoop (Related Projects)
- **Avro** — hệ thống tuần tự hóa dữ liệu (data serialization).
- **HBase** — column-family database phân tán, khả năng mở rộng cao *(đã học ở Lecture 1)*.
- **Cassandra** — column-family database phân tán, khả năng mở rộng cao *(đã học ở Lecture 1)*.
- **ZooKeeper** — dịch vụ điều phối (coordination) hiệu năng cao cho các ứng dụng phân tán.
- **Hive** — data warehouse: truy vấn ad-hoc & tổng hợp dữ liệu (SQL-like, đã nhắc ở Lecture 1).
- **Pig** — ngôn ngữ luồng dữ liệu bậc cao (high-level data-flow language) và framework thực thi cho tính toán song song.
- **Chukwa** — hệ thống thu thập dữ liệu (data collection) để quản lý các hệ thống phân tán lớn.
- **Mahout** — thư viện machine learning và khai phá dữ liệu (data mining) có khả năng mở rộng.

---

## 5. MapReduce trong các hệ thống khác — ngoài Hadoop "chính chủ"

### 5.1. Amazon Elastic MapReduce (EMR)
Dịch vụ MapReduce chạy trên hạ tầng Cloud của Amazon — cho phép chạy Hadoop/Spark **không cần tự dựng cụm máy vật lý**.

### 5.2. Apache Spark
- 1 **engine cho xử lý dữ liệu phân tán**, có thể chạy trên **Hadoop YARN, Apache Mesos, hoặc standalone**...
- Có thể **truy cập dữ liệu từ HDFS, Cassandra, HBase, AWS S3** — tức Spark không "sở hữu" storage riêng, nó chỉ là lớp **xử lý** (tính toán) chạy trên các storage đã có sẵn.
- **Có thể làm MapReduce**, và **nhanh hơn Hadoop thuần rất nhiều** — theo công bố: **10x nhanh hơn khi đọc từ đĩa, 100x khi dữ liệu ở trong RAM**.
- **Lý do chính:** Spark giữ **dữ liệu trung gian trong RAM** (memory) thay vì ghi/đọc liên tục từ đĩa như Hadoop MapReduce truyền thống (nhớ lại mục 3.8: Hadoop MapReduce ghi kết quả trung gian ra **local disk**, còn Spark cố gắng **giữ trong RAM** càng nhiều càng tốt).
- Viết task MapReduce bằng nhiều ngôn ngữ: **Java, Scala, Python, R**. (homepage: spark.apache.org)

**Ví dụ thật: Word Count bằng Spark Shell (ngôn ngữ Scala):**
```scala
val textFile = sc.textFile("hdfs://...")
val counts = textFile.flatMap(line => line.split(" "))
                 .map(word => (word, 1))
                 .reduceByKey(_ + _)
counts.saveAsTextFile("hdfs://...")
```
→ Đọc từng bước: `flatMap` tách mỗi dòng thành nhiều từ (tương đương bước map "phát ra từng từ"), `.map(word => (word, 1))` sinh cặp `(từ, 1)` (chính xác là hàm map trong MapReduce), `.reduceByKey(_ + _)` gom theo key và cộng dồn (chính là Shuffle + Reduce hợp lại thành 1 dòng code!). → Đây là minh chứng cho thấy: **API của Spark "gói" cả map/shuffle/reduce vào vài dòng code rất ngắn**, dễ viết hơn nhiều so với Java thuần của Hadoop ở mục 4.5.

### 5.3. MapReduce trong MongoDB — nối lại với Lecture 1
Ngay cả **document database** như MongoDB (đã học ở Lecture 1) cũng **hỗ trợ chạy MapReduce** trên collection của nó.

**Ví dụ thật (nguyên văn từ slide):** giả sử có collection `accesses`:
```json
{
  "user_id": <ObjectId>,
  "login_time": <thời điểm user đăng nhập>,
  "logout_time": <thời điểm user đăng xuất>,
  "access_type": <loại truy cập>
}
```
**Bài toán:** tính mỗi user đã đăng nhập tổng bao nhiêu thời gian, **chỉ tính các lượt truy cập loại "regular"**.
```javascript
db.accesses.mapReduce(
  function() { emit(this.user_id, this.logout_time - this.login_time); },
  function(key, values) { return Array.sum(values); },
  {
    query: { access_type: "regular" },
    out: "access_times"
  }
)
```
→ Đọc code: hàm đầu (`function() {...}`) chính là **map** — với mỗi document thỏa điều kiện `query`, phát ra cặp `(user_id, thời gian online = logout - login)`. Hàm thứ hai (`function(key, values) {...}`) chính là **reduce** — cộng tổng (`Array.sum`) toàn bộ thời gian của từng user. Kết quả được ghi ra collection mới tên `access_times`.
→ **Ý nghĩa:** dù bạn đang dùng 1 document DB (tưởng như "không liên quan" đến MapReduce của Hadoop/Google), khái niệm **map + reduce vẫn là 1 ngôn ngữ chung** để diễn đạt các phép tính tổng hợp phân tán — MongoDB chỉ đơn giản là cho bạn viết map/reduce bằng JavaScript ngay trong query.

---

## 6. Tóm tắt siêu ngắn để ôn nhanh trước khi vào lớp / thi

- **Vấn đề gốc:** dữ liệu quá lớn, phải phân tán; máy hỏng là chuyện thường → cần **redundancy** (lưu dư thừa) + **task độc lập** (dễ restart khi lỗi).
- **GFS** = hệ file phân tán của Google: chia file thành **chunk 64MB**, nhân bản **3 bản** trên các rack khác nhau, có **1 master giữ metadata**, dữ liệu thật đi thẳng client↔chunkserver.
- **MapReduce** = mô hình lập trình 3 bước: **Map (biến đổi) → Shuffle (gom theo key, tự động) → Reduce (tổng hợp)**. Người dùng chỉ viết `map` và `reduce`.
- **Combiner** = tối ưu tùy chọn: gộp cục bộ trước khi shuffle, giảm tải mạng — chỉ dùng được khi hàm reduce commutative + associative.
- **7 thành phần đầy đủ của framework:** Input reader → Map → Combiner → Partition → Comparator → Reduce → Output writer.
- **Hạn chế của MapReduce:** mô hình lập trình cứng (chỉ 2 pha), không có data model → Google giải bằng **BigTable** (nối với Lecture 1: Cassandra/HBase đi theo hướng này).
- **Hadoop** = bản mã nguồn mở của GFS+MapReduce: **HDFS** (lưu trữ, NameNode/DataNode, block 128MB) + **YARN** (quản lý tài nguyên) + **Hadoop MapReduce** (JobTracker/TaskTracker) — mỗi node vừa là DataNode vừa là TaskTracker để "đưa tính toán đến gần dữ liệu".
- **Ngoài Hadoop:** **Spark** làm MapReduce nhanh hơn nhờ giữ dữ liệu trong RAM (10x-100x); **MongoDB** cũng hỗ trợ mapReduce ngay trong query JavaScript; **Amazon EMR** cho chạy MapReduce trên Cloud.

---

## Nguồn tham khảo (nguyên văn từ slide gốc)
- Dean, J. & Ghemawat, S. *MapReduce: Simplified Data Processing on Large Clusters*. In OSDI 2004 (pp 137–149).
- Firas Abuzaid, Perth Charernwattanagul (2014). Lecture 8 "NoSQL" của môn CS145, Stanford.
- J. Leskovec, A. Rajaraman, and J. D. Ullman. *Mining of Massive Datasets*. 2014.
- I. Holubová, J. Kosek, K. Minařík, D. Novák. *Big Data a NoSQL databáze*. Praha: Grada Publishing, 2015.
- Ghemawat, S., Gobioff, H., & Leung, S.-T. *The Google File System* — dl.acm.org/citation.cfm?id=945450
- hadoop.apache.org, spark.apache.org
