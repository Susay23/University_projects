using System.Text.RegularExpressions;
using MongoDB.Bson;
using MongoDB.Driver;
using ScpMongo.Models;

namespace ScpMongo.Data;

/// <summary>
/// Toàn bộ thao tác với MongoDB nằm ở đây. Program.cs chỉ lo menu và nhập liệu.
/// </summary>
public class ScpRepository
{
    private readonly IMongoDatabase _db;
    private readonly IMongoCollection<Scp> _col;

    public ScpRepository(string connectionString, string dbName = "scp_db", string collectionName = "scp")
    {
        var settings = MongoClientSettings.FromConnectionString(connectionString);
        settings.ServerSelectionTimeout = TimeSpan.FromSeconds(5); // báo lỗi nhanh nếu chưa bật MongoDB
        var client = new MongoClient(settings);
        _db = client.GetDatabase(dbName);
        _col = _db.GetCollection<Scp>(collectionName);
    }

    /// <summary>Kiểm tra kết nối (ném exception nếu không kết nối được).</summary>
    public void Ping() => _db.RunCommand<BsonDocument>(new BsonDocument("ping", 1));

    /// <summary>Tạo unique index cho item_number để không thêm trùng mã SCP.</summary>
    public void EnsureIndexes()
    {
        var keys = Builders<Scp>.IndexKeys.Ascending(x => x.ItemNumber);
        _col.Indexes.CreateOne(new CreateIndexModel<Scp>(keys, new CreateIndexOptions { Unique = true }));
    }

    // ===================== CREATE =====================

    /// <summary>Thêm 1 SCP. Trả về false nếu mã đã tồn tại.</summary>
    public bool Add(Scp scp)
    {
        try
        {
            _col.InsertOne(scp);
            return true;
        }
        catch (MongoWriteException ex) when (ex.WriteError.Category == ServerErrorCategory.DuplicateKey)
        {
            return false;
        }
    }

    /// <summary>Thêm nhiều SCP một lần; bỏ qua các mã đã có. Trả về số document thực sự được thêm.</summary>
    public int AddMany(IEnumerable<Scp> items)
    {
        var list = items.ToList();
        if (list.Count == 0) return 0;
        try
        {
            _col.InsertMany(list, new InsertManyOptions { IsOrdered = false });
            return list.Count;
        }
        catch (MongoBulkWriteException<Scp> ex)
        {
            // IsOrdered = false: các bản ghi trùng bị lỗi nhưng những bản ghi còn lại vẫn được thêm
            return (int)ex.Result.InsertedCount;
        }
    }

    // ===================== READ =====================

    public List<Scp> GetAll() =>
        _col.Find(FilterDefinition<Scp>.Empty).SortBy(x => x.Number).ToList();

    public Scp? FindByItemNumber(string itemNumber) =>
        _col.Find(x => x.ItemNumber == itemNumber).FirstOrDefault();

    /// <summary>Tìm theo tên chứa từ khóa (không phân biệt hoa/thường).</summary>
    public List<Scp> SearchByName(string keyword)
    {
        var regex = new BsonRegularExpression(Regex.Escape(keyword), "i");
        var filter = Builders<Scp>.Filter.Regex(x => x.Name, regex);
        return _col.Find(filter).SortBy(x => x.Number).ToList();
    }

    /// <summary>Lọc theo phân loại (không phân biệt hoa/thường), ví dụ "keter".</summary>
    public List<Scp> FindByClass(string objectClass)
    {
        var regex = new BsonRegularExpression("^" + Regex.Escape(objectClass) + "$", "i");
        var filter = Builders<Scp>.Filter.Regex(x => x.ObjectClass, regex);
        return _col.Find(filter).SortBy(x => x.Number).ToList();
    }

    /// <summary>Các SCP chưa có phân loại (null hoặc thiếu trường).</summary>
    public List<Scp> FindMissingClass()
    {
        var filter = Builders<Scp>.Filter.Eq(x => x.ObjectClass, null);
        return _col.Find(filter).SortBy(x => x.Number).ToList();
    }

    // ===================== UPDATE =====================

    public bool UpdateClass(string itemNumber, string newClass)
    {
        var update = Builders<Scp>.Update.Set(x => x.ObjectClass, newClass);
        var result = _col.UpdateOne(x => x.ItemNumber == itemNumber, update);
        return result.MatchedCount > 0;
    }

    public bool UpdateName(string itemNumber, string newName)
    {
        var update = Builders<Scp>.Update.Set(x => x.Name, newName);
        var result = _col.UpdateOne(x => x.ItemNumber == itemNumber, update);
        return result.MatchedCount > 0;
    }

    // ===================== DELETE =====================

    public bool DeleteByItemNumber(string itemNumber) =>
        _col.DeleteOne(x => x.ItemNumber == itemNumber).DeletedCount > 0;

    public long DeleteByClass(string objectClass)
    {
        var regex = new BsonRegularExpression("^" + Regex.Escape(objectClass) + "$", "i");
        var filter = Builders<Scp>.Filter.Regex(x => x.ObjectClass, regex);
        return _col.DeleteMany(filter).DeletedCount;
    }

    public long DeleteAll() =>
        _col.DeleteMany(FilterDefinition<Scp>.Empty).DeletedCount;

    // ===================== AGGREGATE =====================

    /// <summary>Đếm số SCP theo từng phân loại (tương đương GROUP BY trong SQL).</summary>
    public List<(string ObjectClass, int Count)> CountByClass()
    {
        var rows = _col.Aggregate()
            .Group(x => x.ObjectClass, g => new { ObjectClass = g.Key, Count = g.Count() })
            .ToList();

        return rows
            .Select(r => (r.ObjectClass ?? "(chưa có phân loại)", r.Count))
            .OrderByDescending(r => r.Item2)
            .ToList();
    }

    public long CountAll() => _col.CountDocuments(FilterDefinition<Scp>.Empty);
}
