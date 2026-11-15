# SCP Console App (C# + MongoDB)

Bài luyện tập NoSQL: ứng dụng console thực hiện CRUD trên MongoDB với dữ liệu SCP (SCP-002 → SCP-040).

## Chạy thử

Cần: Docker Desktop, .NET SDK 8 trở lên.

```bash
docker compose up -d        # bật MongoDB (xem docker ps, chờ trạng thái healthy)
dotnet run                  # chạy ứng dụng (lần đầu sẽ tải gói MongoDB.Driver)
```

Trong menu, chọn **2** để nạp dữ liệu mẫu, rồi thử các chức năng còn lại.

Chuỗi kết nối mặc định (khớp docker-compose.yml):
`mongodb://admin:changeme123@localhost:27017/?authSource=admin`
Muốn đổi, đặt biến môi trường `MONGO_URI`.

## Cấu trúc

| File | Vai trò |
|---|---|
| `Models/Scp.cs` | Lớp model, ánh xạ 1 document (item_number, number, name, object_class, source_url) |
| `Data/ScpRepository.cs` | Mọi thao tác MongoDB: insert, find, update, delete, aggregate, index |
| `Program.cs` | Menu console, nhập liệu an toàn, xác nhận trước khi xóa |
| `Data/scp_series1_seed.json` | Dữ liệu mẫu 38 SCP |

## Chức năng ↔ lệnh MongoDB

| Menu | Phương thức | Lệnh MongoDB tương ứng |
|---|---|---|
| 1 | `Add` | `insertOne` |
| 2 | `AddMany` | `insertMany` |
| 3 | `GetAll` | `find()` + `sort({number:1})` |
| 4 | `FindByItemNumber` | `find({item_number: ...})` |
| 5 | `SearchByName` | `find({name: /từ khóa/i})` |
| 6 | `FindByClass` | `find({object_class: /^keter$/i})` |
| 7 | `FindMissingClass` | `find({object_class: null})` |
| 8, 9 | `UpdateClass`, `UpdateName` | `updateOne` + `$set` |
| 10 | `DeleteByItemNumber` | `deleteOne` |
| 11 | `DeleteByClass` | `deleteMany({object_class: ...})` |
| 12 | `DeleteAll` | `deleteMany({})` |
| 13 | `CountByClass` | `aggregate([{ $group: {_id: "$object_class", count: {$sum: 1}} }])` |
| (khởi động) | `EnsureIndexes` | `createIndex({item_number: 1}, {unique: true})` |

## Lưu ý dữ liệu

- SCP-023, SCP-024 chưa có `object_class` (để `null`), cần điền tay sau khi mở trang wiki. Có thể dùng menu 7 để tìm và menu 8 để cập nhật.
- SCP-040 ghi "Anomalous Human" theo trang wiki, nên đối chiếu lại.
- SCP-029 bị bỏ vì chỉ là trang giữ chỗ (staff placeholder).
- Nội dung SCP Foundation theo giấy phép CC BY-SA 3.0, nên giữ `source_url` để ghi nguồn.

## Xem dữ liệu trực tiếp trong MongoDB

```bash
docker exec -it mongodb mongosh -u admin -p changeme123 --authenticationDatabase admin scp_db
> db.scp.find({object_class: "Keter"})
```
