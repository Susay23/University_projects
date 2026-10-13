#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned char byte;

static bool readFile(const char* filename, vector<std::byte>& data){
    FILE* f = fopen(filename, "rb");
    if(!f) return false;
    int c;
    while ((c = fgetc(f))!=EOF){
        data.push_back((std::byte)c);
    }
    fclose(f);
    return true;
}

static vector<std::byte> byteStuffFrame(const std::byte* p, int n, std::byte flag, std::byte esc){
    vector<std::byte> frame;
    frame.push_back(flag);
    for(int i = 0; i<n;i++){
        if(p[i] == flag || p[i] == esc){
            frame.push_back(esc);
        }
        frame.push_back(p[i]);
    }
    frame.push_back(flag);
    return frame;
}

static vector<std::byte> byteUnstuff(const vector<std::byte>& stream, std::byte flag, std::byte esc) {
    vector<std::byte> out;
    bool inFrame = false;
    for (size_t i = 0; i < stream.size(); i++) {
        std::byte b = stream[i];
        if (!inFrame) {
            if (b == flag) inFrame = true;        // gap co mo khung
        } else if (b == esc) {
            i++;                                  // byte sau ESC la du lieu that, kể cả khi no trung FLAG
            if (i < stream.size()) out.push_back(stream[i]);
        } else if (b == flag) {
            inFrame = false;                      // gap co dong khung
        } else {
            out.push_back(b);
        }
    }
    return out;
}

int framing(char* filename, int len, std::byte flag, std::byte esc) {
    if (len <= 0 || flag == esc) {
        return -1;
    }
    vector<std::byte> data;
    if (!readFile(filename, data)){
        return -1;
    }
    vector<std::byte> stream;
    int count = 0;
    for (size_t pos = 0; pos < data.size(); pos += len) {
        int n = (int)min((size_t)len, data.size() - pos);
        vector<std::byte> fr = byteStuffFrame(&data[pos], n, flag, esc);
        count++;
        printf("Khung %d (%d byte du lieu -> %d byte sau khi chen): ", count, n, (int)fr.size());
        for (size_t i = 0; i < fr.size(); i++) printf("%02X ", std::to_integer<int>(fr[i]));
        printf("\n");
        stream.insert(stream.end(), fr.begin(), fr.end());
    }
    printf("Kiem tra tach khung: %s\n", byteUnstuff(stream, flag, esc) == data ? "DUNG" : "SAI");
    return count;
}

static string bitStuffFrame(const std::byte* p, int n) {
    const string FLAG = "01111110";
    string bits;
    int ones = 0;
    for (int i = 0; i < n; i++) {
        for (int k = 7; k >= 0; k--) {    
            int bit = (std::to_integer<int>(p[i]) >> k) & 1;
            bits += (char)('0' + bit);
            if (bit) {
                if (++ones == 5) { bits += '0'; ones = 0; }
            } else {
                ones = 0;
            }
        }
    }
    return FLAG + bits + FLAG;
}

static string bitUnstuff(const string& frame) {
    string body = frame.substr(8, frame.size() - 16), out;
    int ones = 0;
    for (size_t i = 0; i < body.size(); i++) {
        out += body[i];
        if (body[i] == '1') {
            if (++ones == 5) { i++; ones = 0; }
        } else {
            ones = 0;
        }
    }
    return out;
}

int framing_bits(char* filename, int len) {
    if (len <= 0) return -1;
    vector<std::byte> data;
    if (!readFile(filename, data)) return -1;
 
    int count = 0;
    bool ok = true;
    for (size_t pos = 0; pos < data.size(); pos += len) {
        int n = (int)min((size_t)len, data.size() - pos);
        string fr = bitStuffFrame(&data[pos], n);
        count++;
        printf("Khung %d (%d byte du lieu): %s\n", count, n, fr.c_str());
        // doi chieu voi chuoi bit goc cua khung nay
        string orig;
        for (int i = 0; i < n; i++)
           for (int k = 7; k >= 0; k--) 
                orig += (char)('0' + (((std::to_integer<int>(data[pos + i]) >> k) & 1)));
        if (bitUnstuff(fr) != orig) ok = false;
    }
    printf("Kiem tra tach khung: %s\n", ok ? "DUNG" : "SAI");
    return count;
}

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

int main(int argc, char** argv) {
    string name = (argc >= 2) ? argv[1] : "text.txt";
    int len = (argc >= 3) ? atoi(argv[2]) : 10;
 
    string path = findFile(name);
    if (path.empty()) {
        printf("Loi: khong tim thay file '%s'\n", name.c_str());
        printf("Hay dat file canh file .cpp, o thu muc cha cua thu muc build, hoac truyen duong dan day du.\n");
        return 1;
    }
    char* filename = (char*)path.c_str();
 
    printf("File: %s | Kich thuoc khung: %d byte\n\n", filename, len);
    printf("=== Byte stuffing (FLAG=0x7E, ESC=0x7D) ===\n");
    int a = framing(filename, len, (std::byte)0x7E, (std::byte)0x7D);
    if (a < 0) { printf("Loi: tham so sai (len phai > 0)\n"); return 1; }
    printf("Tong so khung: %d\n\n", a);
 
    printf("=== Bit stuffing (co 01111110) ===\n");
    int b = framing_bits(filename, len);
    printf("Tong so khung: %d\n", b);
    return 0;
}