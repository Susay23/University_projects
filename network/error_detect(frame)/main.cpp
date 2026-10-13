// parity_lrc.cpp - Bit kiem tra chan (VRC) cho moi byte + tong kiem tra LRC cuoi khung
// Bien dich: g++ -std=c++11 -Wall -Wextra -o parity parity_lrc.cpp
// Chay:      ./parity [ten_file] [len]    (mac dinh: text.txt, 5 byte du lieu moi khung)
//            ./parity test                (tu kiem tra)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

typedef unsigned char u8;   // dung u8 thay vi "byte" de tranh trung ten std::byte cua C++17

// So bit 1 trong mot byte
static int ones(u8 x) {
    int c = 0;
    for (; x; x >>= 1) c += x & 1;
    return c;
}

// ===================== PHAN 1: DU LIEU 7 BIT =====================
// Moi byte du lieu: bit 7 = bit chan (VRC), bit 6..0 = 7 bit du lieu.
// Bit chan duoc chon sao cho TONG SO BIT 1 CUA BYTE LA CHAN.
// Cuoi khung them 1 byte LRC = XOR cua tat ca cac byte (da kem bit chan) o tren.
// Khung = [d1|p][d2|p]...[dn|p][LRC]
vector<u8> buildFrame7(const u8* d, int n) {
    vector<u8> f;
    u8 lrc = 0;
    for (int i = 0; i < n; i++) {
        if (d[i] > 0x7F) return vector<u8>();          // khong phai du lieu 7 bit -> tu choi
        u8 b = (u8)(d[i] | ((ones(d[i]) & 1) << 7));   // bit 7 = bit chan
        f.push_back(b);
        lrc ^= b;
    }
    f.push_back(lrc);
    return f;
}

// Kiem tra mot khung: tra ve -1 neu co loi, 0 neu khong phat hien loi
int error_detect(const vector<u8>& frame) {
    if (frame.empty()) return -1;                      // khung rong thi khong hop le
    u8 x = 0;
    for (size_t i = 0; i < frame.size(); i++) {
        if (ones(frame[i]) & 1) return -1;             // 1) moi byte phai co so bit 1 chan (kiem tra VRC)
        x ^= frame[i];
    }
    return (x == 0) ? 0 : -1;                          // 2) XOR toan khung (gom ca LRC) phai bang 0
}

// Lay lai du lieu 7 bit tu khung (bo bit chan va byte LRC)
vector<u8> payload7(const vector<u8>& f) {
    vector<u8> out;
    for (size_t i = 0; i + 1 < f.size(); i++) out.push_back((u8)(f[i] & 0x7F));
    return out;
}

// ===================== PHAN 2: DU LIEU 8 BIT =====================
// Y tuong: khong co cho de chua them bit chan trong 1 byte 8 bit du lieu.
// Ta CHIA LAI day bit thanh cac nhom 7 bit (nhom cuoi dem them bit 0),
// roi dung lai y nguyen phan 7 bit o tren. error_detect() khong can doi.
static vector<u8> pack8to7(const u8* d, int n) {
    vector<u8> out;
    int acc = 0, nb = 0;
    for (int i = 0; i < n; i++)
        for (int k = 7; k >= 0; k--) {
            acc = (acc << 1) | ((d[i] >> k) & 1);
            if (++nb == 7) { out.push_back((u8)acc); acc = 0; nb = 0; }
        }
    if (nb > 0) out.push_back((u8)(acc << (7 - nb)));  // nhom cuoi: dem bit 0
    return out;
}

static vector<u8> unpack7to8(const vector<u8>& s) {
    vector<u8> out;
    int acc = 0, nb = 0;
    for (size_t i = 0; i < s.size(); i++)
        for (int k = 6; k >= 0; k--) {
            acc = (acc << 1) | ((s[i] >> k) & 1);
            if (++nb == 8) { out.push_back((u8)acc); acc = 0; nb = 0; }
        }
    return out;   // cac bit con lai (< 8) la bit dem, bo di
}

vector<u8> buildFrame8(const u8* d, int n) {
    vector<u8> s = pack8to7(d, n);
    return buildFrame7(s.empty() ? NULL : &s[0], (int)s.size());
}

vector<u8> payload8(const vector<u8>& f) {
    return unpack7to8(payload7(f));
}

// ===================== TIEN ICH IN =====================
static void printHex(const vector<u8>& f) {
    for (size_t i = 0; i < f.size(); i++) printf("%02X ", f[i]);
    printf("\n");
}
static void printBits(const vector<u8>& f) {   // dang  p|ddddddd  (p la bit chan)
    for (size_t i = 0; i < f.size(); i++) {
        printf("%d|", (f[i] >> 7) & 1);
        for (int k = 6; k >= 0; k--) printf("%d", (f[i] >> k) & 1);
        printf(" ");
    }
    printf("\n");
}

// Tim file o nhieu cho (thu muc hien tai, 1..4 cap thu muc cha, canh file .cpp)
static string findFile(const string& name) {
    vector<string> cands;
    cands.push_back(name);
    cands.push_back("../" + name);
    cands.push_back("../../" + name);
    cands.push_back("../../../" + name);
    cands.push_back("../../../../" + name);
    string src = __FILE__;
    size_t pos = src.find_last_of("/\\");
    if (pos != string::npos) cands.push_back(src.substr(0, pos + 1) + name);
    for (size_t i = 0; i < cands.size(); i++) {
        FILE* f = fopen(cands[i].c_str(), "rb");
        if (f) { fclose(f); return cands[i]; }
    }
    return "";
}

// ===================== TU KIEM TRA =====================
static void flipBit(vector<u8>& f, int pos) { f[pos / 8] ^= (u8)(1 << (pos % 8)); }

// Dem so to hop 'k' bit bi lat (k = 1..4) ma error_detect KHONG phat hien
static long countUndetected(vector<u8>& f, int k) {
    int B = (int)f.size() * 8;
    long bad = 0;
    int a, b, c, d;
    for (a = 0; a < B; a++) {
        flipBit(f, a);
        if (k == 1) { if (error_detect(f) == 0) bad++; }
        else for (b = a + 1; b < B; b++) {
            flipBit(f, b);
            if (k == 2) { if (error_detect(f) == 0) bad++; }
            else for (c = b + 1; c < B; c++) {
                flipBit(f, c);
                if (k == 3) { if (error_detect(f) == 0) bad++; }
                else for (d = c + 1; d < B; d++) {
                    flipBit(f, d);
                    if (error_detect(f) == 0) bad++;
                    flipBit(f, d);
                }
                flipBit(f, c);
            }
            flipBit(f, b);
        }
        flipBit(f, a);
    }
    return bad;
}

static int selftest() {
    srand(12345);
    int fails = 0;

    // 1) Khung 7 bit: khong loi -> 0; lat 1, 2, 3 bit bat ky -> luon phat hien
    for (int n = 0; n <= 8; n++)
        for (int rep = 0; rep < 5; rep++) {
            u8 d[16];
            for (int i = 0; i < n; i++) d[i] = (u8)(rand() & 0x7F);
            vector<u8> f = buildFrame7(d, n);
            if (error_detect(f) != 0) fails++;
            if (payload7(f) != vector<u8>(d, d + n)) fails++;
            for (int k = 1; k <= 3; k++) fails += (int)countUndetected(f, k);
        }
    printf("[1] Khung 7 bit: lat 1, 2, 3 bit bat ky deu bi phat hien (vet can) -> %s\n", fails ? "SAI" : "DUNG");

    // 2) Khung 8 bit: khu hoi dung va cung tinh chat lat 1, 2, 3 bit
    int f2 = 0;
    for (int n = 0; n <= 40; n++) {
        u8 d[64];
        for (int i = 0; i < n; i++) d[i] = (u8)(rand() & 0xFF);
        vector<u8> f = buildFrame8(d, n);
        if (error_detect(f) != 0) f2++;
        if (payload8(f) != vector<u8>(d, d + n)) f2++;
    }
    for (int n = 1; n <= 5; n++) {
        u8 d[8];
        for (int i = 0; i < n; i++) d[i] = (u8)(rand() & 0xFF);
        vector<u8> f = buildFrame8(d, n);
        for (int k = 1; k <= 3; k++) f2 += (int)countUndetected(f, k);
    }
    printf("[2] Khung 8 bit: khu hoi dung va lat 1, 2, 3 bit deu bi phat hien -> %s\n", f2 ? "SAI" : "DUNG");
    fails += f2;

    // 3) Gioi han: 4 bit tao hinh chu nhat se lot qua (2 byte x 2 cot)
    u8 d[4] = { 'A', 'B', 'C', 'D' };
    vector<u8> f = buildFrame7(d, 4);
    flipBit(f, 0 * 8 + 0); flipBit(f, 0 * 8 + 1);   // byte 0: lat bit 0 va bit 1
    flipBit(f, 1 * 8 + 0); flipBit(f, 1 * 8 + 1);   // byte 1: lat bit 0 va bit 1
    int r = error_detect(f);
    printf("[3] Lat 4 bit theo hinh chu nhat -> error_detect = %d (0 nghia la KHONG phat hien duoc: day la gioi han cua phuong phap)\n", r);
    if (r != 0) fails++;
    vector<u8> g = buildFrame7(d, 4);
    printf("    So to hop 4 bit lot qua o khung 4 byte du lieu: %ld\n", countUndetected(g, 4));

    printf(fails ? "\nCO LOI (%d)\n" : "\nTAT CA DEU DUNG\n", fails);
    return fails ? 1 : 0;
}

// ===================== MAIN =====================
int main(int argc, char** argv) {
    if (argc >= 2 && strcmp(argv[1], "test") == 0) return selftest();

    string name = (argc >= 2) ? argv[1] : "text.txt";
    int len = (argc >= 3) ? atoi(argv[2]) : 5;       // so byte du lieu moi khung
    if (len <= 0) { printf("Loi: len phai > 0\n"); return 1; }

    string path = findFile(name);
    if (path.empty()) { printf("Loi: khong tim thay file '%s'\n", name.c_str()); return 1; }

    FILE* fp = fopen(path.c_str(), "rb");
    vector<u8> data;
    int c;
    while ((c = fgetc(fp)) != EOF) data.push_back((u8)c);
    fclose(fp);

    bool mode7 = true;
    for (size_t i = 0; i < data.size(); i++) if (data[i] > 0x7F) { mode7 = false; break; }

    printf("File: %s | %d byte du lieu moi khung | Che do: %s\n\n", path.c_str(), len,
           mode7 ? "7 bit (bit chan trong moi byte + LRC)" : "8 bit (chia lai thanh nhom 7 bit + bit chan + LRC)");

    int count = 0, okClean = 0, caughtBad = 0, restored = 0;
    for (size_t pos = 0; pos < data.size(); pos += len) {
        int n = (int)min((size_t)len, data.size() - pos);
        const u8* p = &data[pos];
        vector<u8> f = mode7 ? buildFrame7(p, n) : buildFrame8(p, n);
        count++;
        printf("Khung %d (%d byte du lieu -> %d byte)\n", count, n, (int)f.size());
        printf("  hex : "); printHex(f);
        printf("  bit : "); printBits(f);

        int r = error_detect(f);
        printf("  error_detect (khung goc)        = %d\n", r);
        if (r == 0) okClean++;

        vector<u8> bad = f;
        bad[0] ^= 0x08;                                   // gia lap loi: lat bit 3 cua byte dau
        int rb = error_detect(bad);
        printf("  error_detect (da lat 1 bit)     = %d\n", rb);
        if (rb == -1) caughtBad++;

        vector<u8> back = mode7 ? payload7(f) : payload8(f);
        if (back == vector<u8>(p, p + n)) restored++;
        printf("\n");
    }
    printf("Tong so khung: %d | khong loi nhan 0: %d | bi lat 1 bit nhan -1: %d | khoi phuc du lieu dung: %d\n",
           count, okClean, caughtBad, restored);
    return 0;
}