#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct TRIE {
    int to[N][62], idx, cnt[N];
    void init() { memset(to, 0, (sizeof to[0]) * (idx + 1)), memset(cnt, 0, (sizeof cnt[0]) * (idx + 1)), idx = 0; }
private:
    static int index(char x) {
        if(x >= 'a' && x <= 'z') return x - 'a';
        else if(x >= 'A' && x <= 'Z') return x - 'A' + 26;
        else return x - '0' + 52;
    }
    void change(const string& str, bool del = false){
        int now = 0;
        for(char e : str) {
            int i = index(e);
            if(!to[now][i]) to[now][i] = ++ idx;
            now = to[now][i], cnt[now] += (del ? -1 : 1);
        }
    }
public:
    void insert(const string& str) { change(str); }
    void remove(const string& str) { change(str, true); }
    int search(const string& prefix) { //多少个字符串以prefix作为前缀
        int now = 0;
        for(char e : prefix) {
            int i = index(e);
            if(!to[now][i]) return 0;
            now = to[now][i];
        }
        return cnt[now];
    }
} trie;
