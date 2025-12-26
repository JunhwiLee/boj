#include <bits/stdc++.h>
#include <zlib.h>
using namespace std;

// ----- Base64 -----
static const char B64_TABLE[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string base64_encode(const unsigned char* data, size_t len) {
    string out;
    out.reserve(((len + 2) / 3) * 4);

    size_t i = 0;
    while (i + 3 <= len) {
        unsigned int v = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
        out.push_back(B64_TABLE[(v >> 18) & 63]);
        out.push_back(B64_TABLE[(v >> 12) & 63]);
        out.push_back(B64_TABLE[(v >> 6) & 63]);
        out.push_back(B64_TABLE[v & 63]);
        i += 3;
    }

    size_t rem = len - i;
    if (rem == 1) {
        unsigned int v = (data[i] << 16);
        out.push_back(B64_TABLE[(v >> 18) & 63]);
        out.push_back(B64_TABLE[(v >> 12) & 63]);
        out.push_back('=');
        out.push_back('=');
    } else if (rem == 2) {
        unsigned int v = (data[i] << 16) | (data[i + 1] << 8);
        out.push_back(B64_TABLE[(v >> 18) & 63]);
        out.push_back(B64_TABLE[(v >> 12) & 63]);
        out.push_back(B64_TABLE[(v >> 6) & 63]);
        out.push_back('=');
    }
    return out;
}

// ----- File read (binary) -----
vector<unsigned char> read_all_bytes(const string& path) {
    ifstream fin(path, ios::binary);
    if (!fin) throw runtime_error("Failed to open input file: " + path);
    fin.seekg(0, ios::end);
    streamsize n = fin.tellg();
    fin.seekg(0, ios::beg);

    vector<unsigned char> buf((size_t)n);
    if (n > 0 && !fin.read(reinterpret_cast<char*>(buf.data()), n))
        throw runtime_error("Failed to read file: " + path);
    return buf;
}

// ----- zlib compress -----
vector<unsigned char> zlib_compress(const vector<unsigned char>& in, int level = Z_BEST_COMPRESSION) {
    uLongf out_bound = compressBound((uLong)in.size());
    vector<unsigned char> out(out_bound);

    uLongf out_len = out_bound;
    int rc = compress2(out.data(), &out_len, in.data(), (uLong)in.size(), level);
    if (rc != Z_OK) throw runtime_error("zlib compress2 failed: " + to_string(rc));

    out.resize((size_t)out_len);
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    try {
        // 1) trie.txt 읽기
        auto raw = read_all_bytes("trie.txt");

        // 2) zlib 압축
        auto comp = zlib_compress(raw);

        // 3) Base64 인코딩
        string b64 = base64_encode(comp.data(), comp.size());

        // 4) zip.txt 저장 (텍스트)
        ofstream fout("zip.txt", ios::binary);
        if (!fout) throw runtime_error("Failed to open output file: zip.txt");
        fout << b64;
        fout.close();

        return 0;
    } catch (const exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
}
