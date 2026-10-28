# Bài tập 9 – Liên kết mạng với Linux Bridge

Oct 28, 2026 · @student

## 1. Mục tiêu và mô hình mạng

Bài tập dựng mạng LAN 10.0.0.0/24 gồm 8 máy (pc1–pc8) và 2 switch ảo chạy Linux Bridge (switch1, switch2), rồi khảo sát cách switch học địa chỉ MAC thông qua giao thức ARP.

**Mục tiêu:** mô phỏng mạng ảo; thực thi dịch vụ Linux Bridge để liên kết các phân nhánh của một mạng LAN và liên kết 2 mạng LAN với nhau; khảo sát cơ chế hoạt động của Linux Bridge qua giao thức ARP.

**Môi trường thực hiện:** Kathará trên Windows (chạy qua Docker), thư mục bài làm `BaiTap9`.

&#91;image: Hình 3.28 – Mô hình mạng sử dụng trong Bài tập 9\]

| Máy | Nối vào | Collision domain | IP (eth0) | MAC (eth0) |
| --- | --- | --- | --- | --- |
| pc1 | switch1 eth0 (Port 1) | A | 10.0.0.10 | 00:00:00:00:00:10 |
| pc2 | switch1 eth1 (Port 2) | B | 10.0.0.20 | 00:00:00:00:00:20 |
| pc3 | switch1 eth2 (Port 3) | C | 10.0.0.30 | 00:00:00:00:00:30 |
| pc4 | switch1 eth3 (Port 4) | D | 10.0.0.40 | 00:00:00:00:00:40 |
| pc5 | switch2 eth0 (Port 1) | E | 10.0.0.11 | 00:00:00:00:77:10 |
| pc6 | switch2 eth1 (Port 2) | F | 10.0.0.22 | 00:00:00:00:77:20 |
| pc7 | switch2 eth2 (Port 3) | G | 10.0.0.33 | 00:00:00:00:77:30 |
| pc8 | switch2 eth3 (Port 4) | H | 10.0.0.44 | 00:00:00:00:77:40 |

Hai switch nối với nhau bằng cổng eth4 (Port 5) của mỗi bên, qua collision domain K. MAC các cổng của switch1: eth0–eth4 lần lượt là 10:10, 20:20, 30:30, 40:40, 50:50; của switch2: 88:10, 88:20, 88:30, 88:40, 88:50 (đều có tiền tố 00:00:00:00).

**Hai nguyên tắc dùng để giải thích kết quả:**

1. Khi một khung đến một cổng, switch ghi địa chỉ MAC nguồn của khung vào bảng và gắn với cổng đó (học theo địa chỉ nguồn).
2. Để chuyển khung, switch tra địa chỉ MAC đích: nếu đích có trong bảng thì chỉ chuyển ra đúng cổng đó; nếu đích là broadcast hoặc chưa biết thì gửi tràn (flood) ra mọi cổng trừ cổng nhận.

Trong ARP, gói ARP request là broadcast, còn ARP reply và gói ICMP là unicast.

## 2. Cấu hình mạng

Thư mục `BaiTap9` chứa 11 file: `lab.conf`, `pc1.startup` … `pc8.startup`, `switch1.startup`, `switch2.startup`.

### 2.1. File lab.conf

Hai giao diện cùng tên collision domain được nối với nhau bằng một đường dây.

```
LAB_DESCRIPTION="Bai tap 9 - Linux Bridge noi 2 switch"

pc1[0]="A"
pc2[0]="B"
pc3[0]="C"
pc4[0]="D"
pc5[0]="E"
pc6[0]="F"
pc7[0]="G"
pc8[0]="H"

switch1[0]="A"
switch1[1]="B"
switch1[2]="C"
switch1[3]="D"
switch1[4]="K"

switch2[0]="E"
switch2[1]="F"
switch2[2]="G"
switch2[3]="H"
switch2[4]="K"
```

### 2.2. File .startup của các máy pc

Mỗi pc có 1 file cùng khuôn mẫu: đặt địa chỉ MAC cho `eth0`, rồi gán IP và bật giao diện. MAC và IP của từng máy lấy theo bảng ở mục 1. Ví dụ `pc1.startup`:

```
ifconfig eth0 hw ether 00:00:00:00:00:10
ifconfig eth0 10.0.0.10 netmask 255.255.255.0 up
```

### 2.3. File switch1.startup

Bật 5 giao diện, đặt MAC, tạo cầu `br0`, thêm 5 giao diện vào cầu, bật giao thức STP và bật `br0`.

```
ifconfig eth0 up
ifconfig eth0 hw ether 00:00:00:00:10:10
ifconfig eth1 up
ifconfig eth1 hw ether 00:00:00:00:20:20
ifconfig eth2 up
ifconfig eth2 hw ether 00:00:00:00:30:30
ifconfig eth3 up
ifconfig eth3 hw ether 00:00:00:00:40:40
ifconfig eth4 up
ifconfig eth4 hw ether 00:00:00:00:50:50
brctl addbr br0
brctl addif br0 eth0
brctl addif br0 eth1
brctl addif br0 eth2
brctl addif br0 eth3
brctl addif br0 eth4
brctl stp br0 on
ifconfig br0 up
```

### 2.4. File switch2.startup

Giống `switch1.startup`, chỉ khác địa chỉ MAC của các cổng (theo Hình 3.28).

```
ifconfig eth0 up
ifconfig eth0 hw ether 00:00:00:00:88:10
ifconfig eth1 up
ifconfig eth1 hw ether 00:00:00:00:88:20
ifconfig eth2 up
ifconfig eth2 hw ether 00:00:00:00:88:30
ifconfig eth3 up
ifconfig eth3 hw ether 00:00:00:00:88:40
ifconfig eth4 up
ifconfig eth4 hw ether 00:00:00:00:88:50
brctl addbr br0
brctl addif br0 eth0
brctl addif br0 eth1
brctl addif br0 eth2
brctl addif br0 eth3
brctl addif br0 eth4
brctl stp br0 on
ifconfig br0 up
```

## 3. Khởi động mạng và bảng MAC ban đầu

Mạng được khởi động bằng `kathara lstart` trong thư mục `BaiTap9`. Trên switch1 và switch2, bảng MAC của cầu nối được xem bằng lệnh:

```
brctl showmacs br0
```

Cột `port no` cho biết cổng: eth0 = 1, eth1 = 2, eth2 = 3, eth3 = 4, eth4 = 5. Cột `is local?` = yes là địa chỉ MAC của chính cổng của switch (mỗi dòng local xuất hiện 2 lần do cách Linux ghi bảng, không ảnh hưởng kết quả).

&#91;image: Bảng MAC ban đầu của switch1\]

&#91;image: Bảng MAC ban đầu của switch2\]

**Nhận xét.** Chưa có máy pc nào được học, vì chưa pc nào gửi dữ liệu. Tuy nhiên mỗi bảng có sẵn 1 dòng `is local? = no` ở cổng 5: switch1 học `00:00:00:00:88:50` (MAC cổng eth4 của switch2), còn switch2 học `00:00:00:00:50:50` (MAC cổng eth4 của switch1). Đây là do hai switch đang chạy STP nên liên tục gửi cho nhau các khung điều khiển BPDU qua đường nối K; nguồn của khung BPDU là MAC cổng eth4 của switch bên kia, nên switch học được nó theo đúng nguyên tắc học địa chỉ nguồn.

## 4. Phần A – Gửi khung giữa 2 máy cùng nối vào switch1 (pc1 → pc4)

Kết quả: switch1 học được cả pc1 và pc4; switch2 chỉ học được pc1; pc5–pc8 không nhận được gói ICMP, chỉ nhận ARP request.

### 4.1. Các bước thực hiện và kết quả đo được

1. Bắt gói trên hai switch:

   ```
   tcpdump -e -q -w /hostlab/BT9_switch1_A.pcap     (switch1)
   tcpdump -e -q -w /hostlab/BT9_switch2_A.pcap     (switch2)
   ```
2. Trên pc1 gửi dữ liệu tới pc4 khoảng 10 giây rồi dừng: `ping 10.0.0.40`. Kết quả: gửi 10 gói, nhận 10 gói, mất 0%.

&#91;image: pc1 ping pc4\]

3. Dừng tcpdump. tcpdump bắt trên giao diện `br0`, tức là các khung mà cầu nhận được từ các cổng. Kết quả: **switch1 bắt được 24 gói, switch2 chỉ bắt được 1 gói** (lần chạy đầu của switch1 hiện 0 gói vì đã dừng trước khi ping; số liệu tính ở lần chạy thứ hai).

&#91;image: Kết quả tcpdump Phần A trên switch1 và switch2\]

4. Kiểm tra lại bảng MAC bằng `brctl showmacs br0` trên cả hai switch:

&#91;image: Bảng MAC sau Phần A: switch1 (trái), switch2 (phải)\]

| Switch | MAC học được | Máy | Cổng |
| --- | --- | --- | --- |
| switch1 | 00:00:00:00:00:10 | pc1 | 1 (eth0) |
| switch1 | 00:00:00:00:00:40 | pc4 | 4 (eth3) |
| switch2 | 00:00:00:00:00:10 | pc1 | 5 (eth4) |

Trên switch2 không có dòng nào của pc4. Dòng `00:00:00:00:50:50` ở cổng 5 là MAC cổng eth4 của switch1, học được từ khung BPDU của STP (xem mục 3).

### 4.2. Diễn biến các khung

1. pc1 chưa biết MAC của 10.0.0.40 nên gửi **ARP request (broadcast)**. switch1 nhận ở eth0, học pc1 ↔ eth0, rồi gửi tràn ra eth1, eth2, eth3 và eth4.
2. Khung đi qua đường K sang switch2. switch2 nhận ở eth4, học pc1 ↔ eth4, rồi gửi tràn ra eth0–eth3, nên pc5–pc8 nhận được ARP request này.
3. pc4 trả **ARP reply (unicast)** cho pc1. switch1 nhận ở eth3, học pc4 ↔ eth3; vì đã biết pc1 ở eth0 nên chỉ chuyển ra eth0, không chuyển qua đường K.
4. Các gói ICMP echo request/reply giữa pc1 và pc4 đều là unicast và cả hai địa chỉ đã có trong bảng, nên chỉ đi qua eth0 ↔ eth3 của switch1. switch2 không thấy các gói này.

### 4.3. Trả lời câu hỏi

**switch1 có học được địa chỉ của cả 2 máy pc1 và pc4 hay không?**

Có. Bảng MAC của switch1 có pc1 ở cổng 1 (eth0) và pc4 ở cổng 4 (eth3). Cả hai máy đều gửi khung vào switch1 (pc1 gửi ARP request và ICMP echo request, pc4 gửi ARP reply và ICMP echo reply), nên switch1 học được địa chỉ MAC nguồn của cả hai.

**switch2 có học được địa chỉ của cả 2 máy pc1 và pc4 hay không? Nếu không thì tại sao?**

Không. switch2 chỉ học được pc1 (qua cổng 5, eth4), không học được pc4. Lý do: pc1 được học nhờ ARP request là gói broadcast nên switch1 gửi tràn sang switch2. Còn pc4 chưa bao giờ làm nguồn của khung nào đến switch2: ARP reply và ICMP echo reply của pc4 là unicast gửi cho pc1, mà switch1 đã biết pc1 nằm ở eth0 nên không chuyển chúng qua đường K. switch2 không nhận khung nào có MAC nguồn pc4 nên không có gì để học.

**Các máy tính từ pc5 đến pc8 có nhận được gói tin ICMP đến từ pc1 hay không? Nếu không thì chúng chỉ nhận được gói tin có giao thức gì từ pc1?**

Không. pc5–pc8 chỉ nhận được gói **ARP request** (giao thức ARP) của pc1, vì đó là gói broadcast. Bằng chứng từ kết quả đo:

- Trong khi pc1 ping, switch1 bắt được 24 gói còn switch2 chỉ bắt được 1 gói. Nếu các gói ICMP (10 echo request và 10 echo reply) đến được switch2 thì switch2 phải bắt được ít nhất từng ấy gói. Vì ICMP không đến switch2 nên không thể đến pc5–pc8.
- Gói duy nhất switch2 nhận là khung có MAC nguồn pc1 (vì switch2 đã học pc1 ở eth4). Đó chính là ARP request broadcast, và switch2 gửi tràn nó ra eth0–eth3 nên pc5–pc8 chỉ nhận được gói này.

## 5. Phần B – Gửi khung giữa 2 máy nối trên switch1 và switch2 (pc2 → pc7)

Kết quả: cả hai switch đều học được cả pc2 và pc7; pc5, pc6, pc8 không nhận được gói ICMP của pc2.

### 5.1. Các bước thực hiện và kết quả đo được

1. Bắt gói trên hai switch:

   ```
   tcpdump -e -q -w /hostlab/BT9_switch1_B.pcap     (switch1)
   tcpdump -e -q -w /hostlab/BT9_switch2_B.pcap     (switch2)
   ```
2. Trên pc2 gửi dữ liệu tới pc7 khoảng 10 giây rồi dừng: `ping 10.0.0.33`. Kết quả: gửi 11 gói, nhận 11 gói, mất 0%.

&#91;image: pc2 ping pc7\]

3. Dừng tcpdump. Kết quả: **switch1 bắt được 26 gói và switch2 cũng bắt được 26 gói**, tức là toàn bộ cuộc trao đổi đi qua cả hai switch (khác Phần A, khi switch2 chỉ thấy 1 gói).

&#91;image: Kết quả tcpdump Phần B (bảng MAC trên switch1 phía trên là kết quả của Phần A)\]

4. Kiểm tra lại bảng MAC bằng `brctl showmacs br0` trên cả hai switch:

&#91;image: Bảng MAC sau Phần B: switch1 (trái), switch2 (phải)\]

| Switch | MAC học được | Máy | Cổng |
| --- | --- | --- | --- |
| switch1 | 00:00:00:00:00:20 | pc2 | 2 (eth1) |
| switch1 | 00:00:00:00:77:30 | pc7 | 5 (eth4) |
| switch2 | 00:00:00:00:00:20 | pc2 | 5 (eth4) |
| switch2 | 00:00:00:00:77:30 | pc7 | 3 (eth2) |

Các dòng pc1 và pc4 (switch1) và pc1 (switch2) là kết quả còn lại từ Phần A, chưa hết thời gian lưu (ageing timer còn dưới 300 giây).

### 5.2. Diễn biến các khung

1. pc2 gửi **ARP request (broadcast)** hỏi MAC của 10.0.0.33. switch1 nhận ở eth1, học pc2 ↔ eth1 và gửi tràn (kể cả eth4). switch2 nhận ở eth4, học pc2 ↔ eth4 và gửi tràn ra eth0–eth3.
2. pc7 trả **ARP reply (unicast)** cho pc2. switch2 nhận ở eth2, học pc7 ↔ eth2; pc2 đã có trong bảng ở eth4 nên chuyển ra eth4.
3. Khung qua đường K vào eth4 của switch1. switch1 học pc7 ↔ eth4; pc2 đã có trong bảng ở eth1 nên chuyển ra eth1.
4. Các gói ICMP echo request/reply pc2 ↔ pc7 đi theo đúng đường đó: eth1 (switch1) → eth4 (switch1) → eth4 (switch2) → eth2 (switch2), và chiều ngược lại.

### 5.3. Trả lời câu hỏi

**switch1 có học được địa chỉ của cả 2 máy pc2 và pc7 hay không?**

Có. switch1 học pc2 ở cổng 2 (eth1) và học pc7 ở cổng 5 (eth4). pc7 nằm ở nhánh switch2 nên switch1 học nó qua cổng nối liên switch, không phải qua cổng riêng của pc7.

**switch2 có học được địa chỉ của cả 2 máy pc2 và pc7 hay không? Nếu có thì tại sao?**

Có. switch2 học pc7 ở cổng 3 (eth2) và học pc2 ở cổng 5 (eth4). Lý do: pc2 và pc7 nằm ở hai nhánh khác nhau nên mọi khung giữa chung đều phải đi xuyên qua cả hai switch: ARP request của pc2 được gửi tràn sang switch2 (nên switch2 thấy MAC nguồn pc2), còn ARP reply và ICMP echo reply của pc7 xuất phát từ nhánh switch2 rồi đi qua switch2 để sang switch1 (nên cả switch2 lẫn switch1 thấy MAC nguồn pc7). Số gói bắt được bằng nhau trên hai switch (26 gói) cũng cho thấy điều này.

**Các máy tính pc5, pc6 và pc8 có nhận được gói tin ICMP đến từ pc2 hay không? Hãy chứng minh điều đó.**

Không. Chứng minh dựa trên bảng MAC của switch2 sau khi ping:

1. switch2 đã biết pc7 (`00:00:00:00:77:30`) nằm ở cổng 3 (eth2) và pc2 (`00:00:00:00:00:20`) nằm ở cổng 5 (eth4).

2) Mỗi gói ICMP echo request của pc2 là khung unicast có MAC đích là pc7. Vì MAC đích có trong bảng, switch2 chỉ chuyển khung ra đúng cổng 3 (eth2), không gửi tràn ra cổng 1, 2, 4 là các cổng nối pc5, pc6, pc8. Tương tự, echo reply có MAC đích pc2 nên chỉ đi ra cổng 5.
3) Khung duy nhất pc5, pc6, pc8 nhận được là ARP request broadcast lúc đầu của pc2 (switch2 gửi tràn ra mọi cổng), không phải ICMP.

## 6. Kết luận

**Hoạt động "học" địa chỉ MAC của các máy thuộc các phân nhánh khác nhau trong cùng một mạng LAN được kết nối bởi 2 switch ảo:**

1. Switch học địa chỉ MAC theo **địa chỉ nguồn** của khung nhận được ở mỗi cổng, và gắn địa chỉ đó với cổng nhận.
2. Với máy ở nhánh bên kia, switch không học qua cổng riêng của máy đó mà học qua **cổng nối liên switch (eth4, Port 5)**. Ví dụ sau Phần B, switch1 gắn pc7 với eth4 và switch2 gắn pc2 với eth4.
3. Một switch chỉ học được MAC của máy ở nhánh khác khi **có khung của máy đó đi qua switch**. Gói ARP request là broadcast nên lan sang cả hai nhánh, vì vậy MAC của máy hỏi được cả hai switch học (pc1 ở Phần A, pc2 ở Phần B). Gói ARP reply và ICMP là unicast nên chỉ đi dọc đường tới đích, vì vậy MAC của máy trả lời chỉ được những switch nằm trên đường đó học (pc4 chỉ được switch1 học ở Phần A; pc7 được cả hai switch học ở Phần B).
4. Khi hai máy cùng một nhánh trao đổi và đã biết địa chỉ nhau (Phần A), switch chỉ chuyển khung unicast trong nhánh đó và **không chuyển sang nhánh còn lại**, giúp giảm lưu lượng không cần thiết. Khi hai máy ở hai nhánh khác nhau (Phần B), khung phải đi qua cả hai switch nên cả hai switch đều học được cả hai máy.

### Hủy mạng ảo

Sau khi hoàn thành Bài tập 9, mạng ảo được hủy bằng lệnh xóa mạng của Kathará (`lwipe` theo đề, tương đương `kathara lclean` trên bản Kathará mới).
