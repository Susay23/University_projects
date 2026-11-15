using System.Text.Json.Serialization;
using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace ScpMongo.Models;

/// <summary>
/// Một tài liệu SCP. Mỗi object của lớp này tương ứng với 1 document trong collection "scp".
/// [BsonElement] đặt tên trường trong MongoDB, [JsonPropertyName] đặt tên trường khi đọc file JSON mẫu.
/// </summary>
[BsonIgnoreExtraElements]
public class Scp
{
    [BsonId]
    [JsonIgnore]
    public ObjectId Id { get; set; }

    [BsonElement("item_number")]
    [JsonPropertyName("item_number")]
    public string ItemNumber { get; set; } = "";      // ví dụ "SCP-005"

    [BsonElement("number")]
    [JsonPropertyName("number")]
    public int Number { get; set; }                   // ví dụ 5 (để sắp xếp / so sánh)

    [BsonElement("name")]
    [JsonPropertyName("name")]
    public string Name { get; set; } = "";            // ví dụ "Skeleton Key"

    [BsonElement("object_class")]
    [JsonPropertyName("object_class")]
    public string? ObjectClass { get; set; }          // Safe / Euclid / Keter ... (có thể null)

    [BsonElement("source_url")]
    [JsonPropertyName("source_url")]
    public string? SourceUrl { get; set; }            // link wiki (ghi nguồn, giấy phép CC BY-SA 3.0)
}
