#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>

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

static vector<std::byte> bytestuffFrame(const std::byte* p, int n, std::byte flag, std::byte esc){
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
            if (b == flag) inFrame = true;
        } else if(b==esc){
            i++;
            if (i < stream.size()) out.push_back(stream[i]);
        } else if(b == flag){
            inFrame = false; 
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

}

