using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;
using ScpMongo.Data;
using ScpMongo.Models;

namespace ScpMongo;

public class Program
{
    // Chuỗi kết nối mặc định khớp với docker-compose.yml. Có thể đổi bằng biến môi trường MONGO_URI.
    private const string DefaultUri = "mongodb://admin:changeme123@localhost:27017/?authSource=admin";

    public static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.InputEncoding = Encoding.UTF8;

        var uri = Environment.GetEnvironmentVariable("MONGO_URI") ?? DefaultUri;
        var repo = new ScpRepository(uri);

        try
        {
            repo.Ping();
            repo.EnsureIndexes();
        }
        catch (Exception ex)
        {
            Console.WriteLine("❌ Không kết nối được MongoDB. Đã chạy 'docker compose up -d' chưa?");
            Console.WriteLine("   Chi tiết: " + ex.Message);
            return;
        }

        int choice;
        do
        {
            PrintMenu();
            choice = ReadInt("Chọn chức năng: ");
            try
            {
                switch (choice)
                {
                    case 1: AddScp(repo); break;
                    case 2: ImportSeed(repo); break;
                    case 3: PrintTable(repo.GetAll()); break;
                    case 4: FindOne(repo); break;
                    case 5: SearchName(repo); break;
                    case 6: FilterByClass(repo); break;
                    case 7: PrintTable(repo.FindMissingClass()); break;
                    case 8: UpdateClass(repo); break;
                    case 9: UpdateName(repo); break;
                    case 10: DeleteOne(repo); break;
                    case 11: DeleteByClass(repo); break;
                    case 12: DeleteAll(repo); break;
                    case 13: Stats(repo); break;
                    case 0: Console.WriteLine("👋 Tạm biệt!"); break;
                    default: Console.WriteLine("⚠️ Lựa chọn không hợp lệ!"); break;
                }
            }
            catch (Exception ex)
            {
                // Lỗi bất ngờ (mất kết nối, ...) không làm chương trình thoát đột ngột
                Console.WriteLine("❌ Có lỗi xảy ra: " + ex.Message);
            }
        } while (choice != 0);
    }

    // ===================== MENU =====================

    private static void PrintMenu()
    {
        Console.WriteLine();
        Console.WriteLine("====== SCP CONSOLE APP (MongoDB) ======");
        Console.WriteLine(" 1. Thêm SCP mới");
        Console.WriteLine(" 2. Nạp dữ liệu mẫu từ file JSON (SCP-002 → SCP-040)");
        Console.WriteLine(" 3. Xem tất cả");
        Console.WriteLine(" 4. Tìm theo mã (vd: 5 hoặc SCP-005)");
        Console.WriteLine(" 5. Tìm theo tên (chứa từ khóa)");
        Console.WriteLine(" 6. Lọc theo phân loại (Safe / Euclid / Keter ...)");
        Console.WriteLine(" 7. Liệt kê SCP chưa có phân loại");
        Console.WriteLine(" 8. Cập nhật phân loại");
        Console.WriteLine(" 9. Cập nhật tên");
        Console.WriteLine("10. Xóa theo mã");
        Console.WriteLine("11. Xóa theo phân loại");
        Console.WriteLine("12. Xóa toàn bộ");
        Console.WriteLine("13. Thống kê số lượng theo phân loại");
        Console.WriteLine(" 0. Thoát");
    }

    // ===================== CHỨC NĂNG =====================

    private static void AddScp(ScpRepository repo)
    {
        var item = ReadItemNumber("Mã SCP (vd: 41 hoặc SCP-041): ");
        if (item == null) return;
        var name = ReadRequired("Tên: ");
        Console.Write("Phân loại (Enter để bỏ trống): ");
        var cls = Console.ReadLine()?.Trim();

        var scp = new Scp
        {
            ItemNumber = item,
            Number = int.Parse(item.Substring(4)),
            Name = name,
            ObjectClass = string.IsNullOrWhiteSpace(cls) ? null : cls,
            SourceUrl = $"https://scp-wiki.wikidot.com/{item.ToLowerInvariant()}"
        };

        Console.WriteLine(repo.Add(scp) ? $"✅ Đã thêm {item}" : $"⚠️ {item} đã tồn tại, không thêm.");
    }

    private static void ImportSeed(ScpRepository repo)
    {
        var path = Path.Combine(AppContext.BaseDirectory, "Data", "scp_series1_seed.json");
        if (!File.Exists(path))
        {
            Console.WriteLine("❌ Không tìm thấy file: " + path);
            return;
        }

        var json = File.ReadAllText(path, Encoding.UTF8);
        var items = JsonSerializer.Deserialize<List<Scp>>(json) ?? new List<Scp>();
        var inserted = repo.AddMany(items);
        Console.WriteLine($"✅ Đã nạp {inserted}/{items.Count} SCP (các mã đã tồn tại sẽ được bỏ qua).");
    }

    private static void FindOne(ScpRepository repo)
    {
        var item = ReadItemNumber("Mã SCP cần tìm: ");
        if (item == null) return;
        var scp = repo.FindByItemNumber(item);
        if (scp == null) Console.WriteLine($"⚠️ Không có {item}.");
        else PrintDetail(scp);
    }

    private static void SearchName(ScpRepository repo)
    {
        var keyword = ReadRequired("Từ khóa trong tên: ");
        PrintTable(repo.SearchByName(keyword));
    }

    private static void FilterByClass(ScpRepository repo)
    {
        var cls = ReadRequired("Phân loại: ");
        PrintTable(repo.FindByClass(cls));
    }

    private static void UpdateClass(ScpRepository repo)
    {
        var item = ReadItemNumber("Mã SCP cần cập nhật: ");
        if (item == null) return;
        var cls = ReadRequired("Phân loại mới: ");
        Console.WriteLine(repo.UpdateClass(item, cls) ? $"✅ Đã cập nhật phân loại của {item}" : $"⚠️ Không có {item}.");
    }

    private static void UpdateName(ScpRepository repo)
    {
        var item = ReadItemNumber("Mã SCP cần cập nhật: ");
        if (item == null) return;
        var name = ReadRequired("Tên mới: ");
        Console.WriteLine(repo.UpdateName(item, name) ? $"✅ Đã cập nhật tên của {item}" : $"⚠️ Không có {item}.");
    }

    private static void DeleteOne(ScpRepository repo)
    {
        var item = ReadItemNumber("Mã SCP cần xóa: ");
        if (item == null) return;
        if (!Confirm($"Xóa {item}?")) return;
        Console.WriteLine(repo.DeleteByItemNumber(item) ? $"🗑️ Đã xóa {item}" : $"⚠️ Không có {item}.");
    }

    private static void DeleteByClass(ScpRepository repo)
    {
        var cls = ReadRequired("Xóa tất cả SCP thuộc phân loại: ");
        if (!Confirm($"Xóa tất cả SCP phân loại '{cls}'?")) return;
        Console.WriteLine($"🗑️ Đã xóa {repo.DeleteByClass(cls)} SCP.");
    }

    private static void DeleteAll(ScpRepository repo)
    {
        Console.Write($"Sẽ xóa TOÀN BỘ {repo.CountAll()} SCP. Gõ XOA để xác nhận: ");
        if (Console.ReadLine()?.Trim() != "XOA")
        {
            Console.WriteLine("Đã hủy.");
            return;
        }
        Console.WriteLine($"🗑️ Đã xóa {repo.DeleteAll()} SCP.");
    }

    private static void Stats(ScpRepository repo)
    {
        var rows = repo.CountByClass();
        if (rows.Count == 0) { Console.WriteLine("(chưa có dữ liệu)"); return; }
        Console.WriteLine("📊 Số SCP theo phân loại:");
        foreach (var (cls, count) in rows)
            Console.WriteLine($"  {cls,-22} {count}");
    }

    // ===================== HIỂN THỊ =====================

    private static void PrintTable(List<Scp> list)
    {
        if (list.Count == 0) { Console.WriteLine("(không có kết quả)"); return; }
        Console.WriteLine($"{"Mã",-9} {"Phân loại",-16} Tên");
        Console.WriteLine(new string('-', 70));
        foreach (var s in list)
            Console.WriteLine($"{s.ItemNumber,-9} {s.ObjectClass ?? "(chưa có)",-16} {s.Name}");
        Console.WriteLine($"Tổng: {list.Count}");
    }

    private static void PrintDetail(Scp s)
    {
        Console.WriteLine($"Mã        : {s.ItemNumber}");
        Console.WriteLine($"Tên       : {s.Name}");
        Console.WriteLine($"Phân loại : {s.ObjectClass ?? "(chưa có)"}");
        Console.WriteLine($"Nguồn     : {s.SourceUrl}");
    }

    // ===================== NHẬP LIỆU AN TOÀN =====================

    private static int ReadInt(string prompt)
    {
        while (true)
        {
            Console.Write(prompt);
            if (int.TryParse(Console.ReadLine(), out var value)) return value;
            Console.WriteLine("⚠️ Vui lòng nhập một số nguyên.");
        }
    }

    private static string ReadRequired(string prompt)
    {
        while (true)
        {
            Console.Write(prompt);
            var s = Console.ReadLine()?.Trim();
            if (!string.IsNullOrEmpty(s)) return s;
            Console.WriteLine("⚠️ Không được để trống.");
        }
    }

    /// <summary>Chuẩn hóa "5", "scp-5", "SCP-005" thành "SCP-005". Trả về null nếu không hợp lệ.</summary>
    private static string? ReadItemNumber(string prompt)
    {
        Console.Write(prompt);
        var input = Console.ReadLine() ?? "";
        var m = Regex.Match(input, @"\d+");
        if (!m.Success || !int.TryParse(m.Value, out var n) || n <= 0)
        {
            Console.WriteLine("⚠️ Mã không hợp lệ.");
            return null;
        }
        return $"SCP-{n:D3}";
    }

    private static bool Confirm(string question)
    {
        Console.Write(question + " (y/n): ");
        return Console.ReadLine()?.Trim().ToLowerInvariant() == "y";
    }
}
