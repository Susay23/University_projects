# Đáp án Bài tập 12 — Vạch đường động RIPv2 với Quagga trên Kathará

> Mọi kết quả dưới đây lấy từ **ảnh chụp trên máy của bạn** (24/11/2026), không phải kết quả mô phỏng.
> Chỗ nào là suy luận chưa kiểm chứng thì mình ghi rõ là **suy luận**.
> Ở các mục có `[Chèn ảnh ...]`, bạn dán ảnh tương ứng của bạn vào.
> Tên file đặt theo ngày 25/11/2026 như bản ghi chép trước; đổi lại nếu cần.

---

## 0. Môi trường và mô hình mạng

- Kathará (Docker), 4 máy ảo `router1`–`router4`, image `kathara/quagga` (Quagga 1.2.4, theo màn hình đăng nhập `ripd`).
- Chạy RIPv2 bằng Quagga: `zebra=yes`, `ripd=yes`, `router rip`, `network 100.1.0.0/16`, `redistribute connected` trên cả 4 router.

| Router | Cổng | Mạng | IP |
|---|---|---|---|
| router1 | eth0 / eth1 / eth2 / eth3 | H / G / E / A | 100.1.0.13/30, 100.1.0.9/30, 100.1.0.1/30, 100.1.1.1/24 |
| router2 | eth0 / eth1 / eth2 | E / F / B | 100.1.0.2/30, 100.1.0.5/30, 100.1.2.1/24 |
| router3 | eth0 / eth1 / eth2 / eth3 | F / G / I / C | 100.1.0.6/30, 100.1.0.10/30, 100.1.0.17/30, 100.1.3.1/24 |
| router4 | eth0 / eth1 / eth2 | D / I / H | 100.1.4.1/24, 100.1.0.18/30, 100.1.0.14/30 |

Mạng E, F, G, H, I là dây nối giữa hai router (/30). Mạng A, B, C, D là LAN của từng router (/24).

> Lưu ý khi làm: image Kathará mặc định không có Quagga (lỗi `/etc/init.d/quagga: No such file or directory`). Đã khắc phục bằng cách thêm vào `lab.conf` dòng `routerN[image]="kathara/quagga"` cho mỗi router.

---

## 1. Câu hỏi ở bước 8: vì sao `network 100.1.0.0/16`, không phải `/24`? Có dùng `/20` được không?

Lệnh `network` quyết định **cổng nào chạy RIP**: cổng có địa chỉ IP nằm trong dải đó sẽ gửi và nhận RIP (Quagga manual: "Set the RIP enable interface by network").

| Dải | Phạm vi | Phủ được gì |
|---|---|---|
| `100.1.0.0/16` | 100.1.0.0 – 100.1.255.255 | Mọi cổng của mô hình (dây nối `100.1.0.x` và LAN `100.1.1.x`–`100.1.4.x`) |
| `100.1.0.0/24` | 100.1.0.0 – 100.1.0.255 | Chỉ các dây nối giữa router. **Không** phủ các cổng LAN A, B, C, D |
| `100.1.0.0/20` | 100.1.0.0 – 100.1.15.255 | **Có**, vì chứa mọi địa chỉ từ `100.1.0.x` đến `100.1.4.x` |

**Kết luận**: dải trong `network` phải chứa địa chỉ của mọi cổng cần chạy RIP. Chọn `/16` là phủ toàn bộ AS; `/20` cũng được vì vẫn phủ hết; `/24` thì các cổng LAN không chạy RIP.

**Bằng chứng từ máy bạn**: trong file bắt gói của router1 có gói RIP với nguồn `100.1.1.1` (cổng `eth3` của router1 ở mạng A). Vậy với `/16`, router1 gửi RIP ra cả mạng LAN A dù mạng đó không có router nào. Với `/24` thì địa chỉ `100.1.1.1` nằm ngoài dải nên cổng này sẽ không gửi.
*(Phần "với /24 thì không gửi" là suy luận theo định nghĩa lệnh, chưa được thử trực tiếp.)*

---

## 2. Bước 9: kiểm tra Quagga đã chạy

Lệnh: `/etc/init.d/quagga status`

Kết quả trên router1 và router2: `ripd watchquagga zebra`. Theo đề, nghĩa là mọi thiết lập RIPv2 trên Quagga đều chính xác.

`[Chèn ảnh: status của router1, router2 (và router3, router4 nếu có)]`

Khi khởi động có hai cảnh báo không ảnh hưởng đến bài:
- `can't open logfile /var/log/zebra/...`: thư mục log không tồn tại trong image nên Quagga không ghi được file log; RIP vẫn chạy đúng.
- `kathara/quagga image is deprecated`: image không còn được cập nhật nhưng vẫn dùng được.

---

## 3. Bước 10: bảng định tuyến và kiểm tra liên thông

### 3.1 Bảng `route -n` (sau khi mạng hội tụ)

**router1**

| Đích | Gateway | Flags | Iface |
|---|---|---|---|
| 100.1.0.0/30 (E) | 0.0.0.0 | U | eth2 |
| 100.1.0.4/30 (F) | 100.1.0.10 | UG | eth1 |
| 100.1.0.8/30 (G) | 0.0.0.0 | U | eth1 |
| 100.1.0.12/30 (H) | 0.0.0.0 | U | eth0 |
| 100.1.0.16/30 (I) | 100.1.0.14 | UG | eth0 |
| 100.1.1.0/24 (A) | 0.0.0.0 | U | eth3 |
| 100.1.2.0/24 (B) | 100.1.0.2 | UG | eth2 |
| 100.1.3.0/24 (C) | 100.1.0.10 | UG | eth1 |
| 100.1.4.0/24 (D) | 100.1.0.14 | UG | eth0 |

**router2**

| Đích | Gateway | Flags | Iface |
|---|---|---|---|
| 100.1.0.0/30 (E) | 0.0.0.0 | U | eth0 |
| 100.1.0.4/30 (F) | 0.0.0.0 | U | eth1 |
| 100.1.0.8/30 (G) | 100.1.0.6 | UG | eth1 |
| 100.1.0.12/30 (H) | 100.1.0.1 | UG | eth0 |
| 100.1.0.16/30 (I) | 100.1.0.6 | UG | eth1 |
| 100.1.1.0/24 (A) | 100.1.0.1 | UG | eth0 |
| 100.1.2.0/24 (B) | 0.0.0.0 | U | eth2 |
| 100.1.3.0/24 (C) | 100.1.0.6 | UG | eth1 |
| 100.1.4.0/24 (D) | 100.1.0.6 | UG | eth1 |

`[Chèn ảnh: route -n của router1 và router2]`

### 3.2 Nhận xét

- Mỗi router có **đủ 9 mạng** của mô hình trong bảng, dù không cấu hình đường tĩnh nào. Các đường này do RIP tự học.
- Mạng nối trực tiếp: cờ `U`, Gateway `0.0.0.0`. Mạng học qua RIP: cờ `UG`, có Gateway là địa chỉ của router kế tiếp.
- Cột `Metric` của `route` đều là 20 cho mọi đường học được, bất kể xa hay gần. Đây không phải số hop RIP. Số hop thật chỉ xem được trong `show ip rip` (mục 5).
- Khi hai đường có cùng số hop (ví dụ router1 đến mạng F có thể qua router2 hoặc router3), RIP chỉ giữ một đường. Đường nào được chọn phụ thuộc vào đường nào được học trước, nên kết quả giữa các lần chạy có thể khác nhau (quan sát thực tế: sau khi bật lại `eth1`, router1 chọn đường khác cho mạng I).

### 3.3 Ping kiểm tra liên thông

| Lệnh | Kết quả |
|---|---|
| Từ router1: `ping -w 7 100.1.4.1` | 7 gói gửi, 7 nhận, mất 0%, TTL=64 |
| Từ router2: `ping -w 7 100.1.0.10` | 7 gói gửi, 7 nhận, mất 0%, TTL=64 |

`[Chèn ảnh: kết quả hai lệnh ping]`

Kết luận: các mạng LAN thông nhau. TTL=64 vì đích nằm ở router kề cạnh (không đi qua router trung gian).

---

## 4. Bước 11: bắt gói RIP

Lệnh trên router1: `tcpdump -i any -w /hosthome/BaiTap12_router1.pcap`, dừng bằng `Ctrl+C`.

Kết quả: bắt được 9 gói, không mất gói nào (`0 packets dropped by kernel`). File được lấy ra máy thật bằng `docker cp` (vì `/hosthome` không nối ra thư mục Windows).

`[Chèn ảnh: kết quả tcpdump]`

---

## 5. Bước 12–13: giao diện `ripd` và `show ip rip`

Lệnh: `telnet localhost ripd`, mật khẩu `zebra`, rồi `show ip rip`.

**router2** (trước khi cắt dây):

| Mã | Mạng | Next hop | Metric | From |
|---|---|---|---|---|
| C(i) | 100.1.0.0/30 | 0.0.0.0 | 1 | self |
| C(i) | 100.1.0.4/30 | 0.0.0.0 | 1 | self |
| R(n) | 100.1.0.8/30 | 100.1.0.6 | 2 | 100.1.0.6 |
| R(n) | 100.1.0.12/30 | 100.1.0.1 | 2 | 100.1.0.1 |
| R(n) | 100.1.0.16/30 | 100.1.0.6 | 2 | 100.1.0.6 |
| R(n) | 100.1.1.0/24 | 100.1.0.1 | 2 | 100.1.0.1 |
| C(i) | 100.1.2.0/24 | 0.0.0.0 | 1 | self |
| R(n) | 100.1.3.0/24 | 100.1.0.6 | 2 | 100.1.0.6 |
| R(n) | 100.1.4.0/24 | 100.1.0.6 | 3 | 100.1.0.6 |

`[Chèn ảnh: show ip rip của router2]`

### So sánh với lệnh `route`

| | `show ip rip` | `route -n` |
|---|---|---|
| Là bảng của | Dịch vụ `ripd` | Nhân Linux (dùng để chuyển gói thật) |
| Mạng đích, next hop | Có | Có, **trùng khớp** với `show ip rip` (đã đối chiếu 6 đường học được của router2) |
| Metric | Số hop thật (1, 2, 3) | Luôn là 20 với đường học được |
| Biết router nào báo (cột `From`) | Có | Không |
| Bộ đếm thời gian (cột `Time`) | Có | Không |
| Tên cổng (`eth0`...) và cờ `U`/`UG` | Không | Có |

### Một số thông tin có ích trên `show ip rip`

- `C(i)` là mạng nối trực tiếp (metric 1, From `self`). `R(n)` là mạng học qua RIP.
- Metric tăng theo số router phải đi qua: mạng D ở router2 có metric 3 vì phải qua hai router (router3 rồi router4).
- Cột `From` cho biết đường do hàng xóm nào báo, cho phép biết một đường sẽ mất nếu hàng xóm đó hỏng.
- Cột `Time` là bộ đếm lùi của timeout 180 giây (ví dụ `02:59` nghĩa là vừa được nghe lại 1 giây trước). Các đường đến từ hai hàng xóm khác nhau (`02:59` và `02:54`) vì hai hàng xóm gửi cập nhật lệch nhau vài giây.

---

## 6. Bước 14: phân tích bằng Wireshark

Gói số 9 trong file bắt: nguồn `100.1.0.10` (router3), 172 byte, `RIPv2 Response`.

`[Chèn ảnh: khung giữa Wireshark của gói này, có mở Internet Protocol, UDP, Routing Information Protocol]`

| Câu hỏi | Trả lời |
|---|---|
| IP đích là bao nhiêu? Broadcast, unicast hay multicast? | **224.0.0.9**, là địa chỉ **multicast** (dành riêng cho RIPv2) |
| Giao thức tầng vận chuyển và cổng? | **UDP**, cổng nguồn **520**, cổng đích **520** |
| Cặp `IP Address – Metric` hiểu thế nào? | Mỗi cặp là một **mạng đích** mà router gửi biết, kèm **số hop từ router gửi tới mạng đó**. Metric 1: nối trực tiếp với router gửi. Metric 2: phải qua thêm một router. Metric 16 nghĩa là không tới được |

Nội dung 6 cặp trong gói của router3:

| Mạng | Metric | Giải thích |
|---|---|---|
| 100.1.0.4 | 1 | Router3 nối trực tiếp (F) |
| 100.1.0.12 | 2 | Học từ router4 (H) |
| 100.1.0.16 | 1 | Nối trực tiếp (I) |
| 100.1.2.0 | 2 | Học từ router2 (B) |
| 100.1.3.0 | 1 | Nối trực tiếp (C) |
| 100.1.4.0 | 2 | Học từ router4 (D) |

Gói không có mạng `100.1.0.8` (G), `100.1.0.0` (E) và `100.1.1.0` (A). Gói này gửi ra cổng nối tới router1. Router3 không báo ngược các mạng nó học từ chính router1 (E, A) và không báo lại mạng của chính cổng gửi (G). Đây là cơ chế **split horizon**.

Kiểm tra bằng độ dài: cooked capture v2 (20 byte) + IP (20) + UDP (8) + đầu RIP (4) + 6 × 20 byte = **172 byte**, khớp với độ dài trong Wireshark.
*(Định dạng 20 byte mỗi cặp và 4 byte đầu RIP là theo RFC 2453; mình chưa mở lại RFC trong phiên này, nhưng phép tính khớp với số liệu thật của bạn.)*

### Router1 nhận RIP từ những router nào?

Lọc: `rip && !(ip.src==100.1.0.1 || ip.src==100.1.0.9 || ip.src==100.1.0.13)`

| Nguồn | Router | Thời điểm thấy |
|---|---|---|
| 100.1.0.2 | router2 | 0,000 s |
| 100.1.0.14 | router4 | 0,254 s và 29,251 s |
| 100.1.0.10 | router3 | 0,254 s và 29,251 s |

`[Chèn ảnh: danh sách gói sau khi lọc]`

Ngoài router3, router1 còn nhận RIP từ **router2 (`100.1.0.2`)** và **router4 (`100.1.0.14`)**. Router2 chỉ xuất hiện một lần vì lần gửi kế tiếp của nó rơi sau khi dừng `tcpdump`.

Hai lần gửi của router3 và router4 cách nhau khoảng 29 giây, xấp xỉ chu kỳ cập nhật 30 giây của RIP.

Trong danh sách còn một gói nguồn `100.1.1.1`: đó là chính router1 gửi ra mạng LAN A (xem mục 1), không phải hàng xóm.

---

## 7. Bước 15–17: cắt dây G giữa router1 và router3

### 7.1 Trước khi cắt (router1, sau khi hội tụ)

Các dòng liên quan đến cổng `eth1` (mạng G):

| Đích | Gateway | Iface |
|---|---|---|
| 100.1.0.4/30 (F) | 100.1.0.10 | eth1 |
| 100.1.0.8/30 (G) | 0.0.0.0 (nối trực tiếp) | eth1 |
| 100.1.0.16/30 (I) | 100.1.0.10 | eth1 |
| 100.1.3.0/24 (C) | 100.1.0.10 | eth1 |

### 7.2 Bước 15–16: tắt `eth1`, ping ngay và xem `route`

Lệnh: `ifconfig eth1 down`, rồi `ping -c 3 -W 1 100.1.0.10`, rồi `route -n`.

- **Ping**: 3 gói gửi, 3 nhận, mất 0%, **TTL=63** (TTL giảm 1 so với bình thường, nghĩa là gói đi vòng qua một router trung gian).
- **Bảng `route`**: đã thay đổi (xem bảng so sánh dưới đây).

`[Chèn ảnh: ifconfig eth1 down, ping và route -n]`

### 7.3 Bước 17: đợi 30 giây, ping và xem `route` lần nữa

Lệnh: `sleep 30; ping -w 7 100.1.0.10; route -n`.

- **Ping**: 7 gói gửi, 7 nhận, mất 0%, TTL=63.
- **Bảng `route`**: giống bảng ngay sau khi cắt (mạng đã ổn định).

`[Chèn ảnh: ping và route -n sau 30 giây]`

### 7.4 Thay đổi trong bảng định tuyến của router1

| Đích | Trước khi cắt | Sau khi cắt |
|---|---|---|
| 100.1.0.4/30 (F) | qua 100.1.0.10 (eth1) | qua **100.1.0.2** (eth2, router2) |
| 100.1.0.8/30 (G) | nối trực tiếp (eth1) | qua **100.1.0.2** (eth2), `UG`, đi vòng qua router2 |
| 100.1.0.16/30 (I) | qua 100.1.0.10 (eth1) | qua **100.1.0.14** (eth0, router4) |
| 100.1.3.0/24 (C) | qua 100.1.0.10 (eth1) | qua **100.1.0.14** (eth0, router4) |

Các dòng còn lại không đổi. Không còn đường nào đi qua `eth1`.

`show ip rip` trên router1 sau khi cắt:

| Mã | Mạng | Next hop | Metric | From |
|---|---|---|---|---|
| C(i) | 100.1.0.0/30 | 0.0.0.0 | 1 | self |
| R(n) | 100.1.0.4/30 | 100.1.0.2 | 2 | 100.1.0.2 |
| R(n) | 100.1.0.8/30 | 100.1.0.2 | **3** | 100.1.0.2 |
| C(i) | 100.1.0.12/30 | 0.0.0.0 | 1 | self |
| R(n) | 100.1.0.16/30 | 100.1.0.14 | 2 | 100.1.0.14 |
| C(i) | 100.1.1.0/24 | 0.0.0.0 | 1 | self |
| R(n) | 100.1.2.0/24 | 100.1.0.2 | 2 | 100.1.0.2 |
| R(n) | 100.1.3.0/24 | 100.1.0.14 | **3** | 100.1.0.14 |
| R(n) | 100.1.4.0/24 | 100.1.0.14 | 2 | 100.1.0.14 |

`[Chèn ảnh: show ip rip của router1 sau khi cắt]`

Mạng G (đã đứt) giờ có metric **3**: router1 → router2 → router3, là đường vòng dài hơn đường trực tiếp (metric 1). Mạng C cũng tăng từ 2 lên 3 vì không còn đi thẳng qua G. Mạng nối trực tiếp (`C(i)`) của router1 giảm từ 4 xuống 3 (mất mạng G).

### 7.5 Ghi chú quan sát: kết quả khác với mô tả của đề

Đề gợi ý rằng ngay sau khi cắt, ping có thể không thành công và bảng `route` chưa đổi; đến khoảng 30 giây sau mới cập nhật. **Trên máy của bạn, ping đã thông và bảng đã đổi ngay** trong vài giây sau khi cắt (giữa hai lệnh chỉ cách nhau thời gian gõ phím).

Nguyên nhân chưa kiểm chứng được. **Suy luận**: RIP có thể gửi cập nhật ngay khi có thay đổi (cập nhật kích hoạt) thay vì đợi đủ chu kỳ 30 giây. Có thể kiểm chứng bằng cách bắt gói `tcpdump` ngay lúc cắt dây, xem có gói RIP đến sớm hơn mốc 30 giây không.

---

## 8. Bước 18: kết luận về hoạt động vạch đường RIPv2

**Về gói tin vạch đường RIPv2**
- Gửi bằng UDP, cổng 520 (cả nguồn và đích), tới địa chỉ multicast 224.0.0.9.
- Nội dung là danh sách các cặp (mạng đích, metric). Router không báo ngược đường đã học từ chính cổng đó (split horizon).
- Gửi định kỳ, khoảng 30 giây một lần.

**Về chi phí (metric)**
- Metric là số hop: mạng nối trực tiếp là 1, mỗi router đi qua thêm cộng 1. Giá trị 16 nghĩa là không tới được.
- Khi có nhiều đường, RIP chọn đường ít hop nhất. Khi bằng nhau thì giữ đường được học trước, nên kết quả có thể khác nhau giữa các lần chạy.

**Về cơ chế tự cập nhật khi hình trạng mạng thay đổi**
- Khi dây G giữa router1 và router3 bị cắt, router1 tự học được đường vòng qua router2 (metric 3) và qua router4 mà không cần cấu hình lại.
- Ping vẫn thông, đường đi tự đổi sang đường vòng.
- Trên máy bạn, việc này diễn ra trong vài giây, nhanh hơn chu kỳ 30 giây của đề.

**Nhận xét của riêng bạn** (tự viết, ví dụ về ưu và nhược điểm của RIP so với vạch đường tĩnh):

> …

---

## 9. Bước 19: dọn dẹp

`kathara wipe` (đề dùng `lwipe`, là lệnh của bản Kathará cũ).

---

## 10. Danh sách ảnh cần chèn

| # | Nội dung | Mục |
|---|---|---|
| 1 | `status` của các router | 2 |
| 2 | `route -n` router1, router2 | 3.1 |
| 3 | Ping router1→router4, router2→router3 | 3.3 |
| 4 | Kết quả `tcpdump` | 4 |
| 5 | `show ip rip` của router2 | 5 |
| 6 | Wireshark: gói từ `100.1.0.10` (IP, UDP, RIP) | 6 |
| 7 | Wireshark: danh sách nguồn sau khi lọc | 6 |
| 8 | `ifconfig eth1 down`, ping, `route -n` | 7.2 |
| 9 | Ping và `route -n` sau 30 giây | 7.3 |
| 10 | `show ip rip` router1 sau khi cắt | 7.4 |

Ảnh nên bổ sung nếu báo cáo yêu cầu "trên các router": `status` của router3 và router4 (hiện bạn mới có router1 và router2).

---

## 11. Nguồn

- Đề bài `DinhTuyen-RIP.pdf` và cấu hình mẫu `router1.zip`.
- Quagga manual, chương RIP (`router rip`, `network`, `redistribute connected`, timers 30/180/120 giây): https://users.cs.fiu.edu/~esj/cnt4504/reading/quagga.pdf
- Wikipedia, *Routing Information Protocol* (UDP 520, 224.0.0.9, metric 16 là không tới được, split horizon): https://ipfs.ssi.eecc.de/ipns/en.wikipedia-on-ipfs.org/wiki/Routing_Information_Protocol
- RFC 2453 *RIP Version 2* (định dạng gói): https://www.rfc-editor.org/rfc/rfc2453
- Image Kathará dùng trong bài: https://hub.docker.com/r/kathara/quagga
