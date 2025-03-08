#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct TRIE01 {
    int nxt[N][2], idx, cnt[N], len;
    void init(int k) { len = k, memset(nxt, 0, (sizeof nxt[0]) * (idx + 1)), memset(cnt, 0, (sizeof cnt[0]) * (idx + 1)), idx = 0; }
    void change(int x, bool del = false){
        int now = 0;
        for(int i= len - 1; i >= 0;i--) {
            int p = (x >> i) & 1;
            if(!nxt[now][p]) nxt[now][p] = ++ idx;
            now = nxt[now][p], cnt[now] += (del ? -1 : 1);
        }
    }
    void insert(int x) { change(x); }
    void remove(int x) { change(x, true); }
    int query(int s, bool large = true){ //查找和s异或后的最大值/最小值
        int now = 0, ans = large ? 0 : (1 << len) - 1;
        bool st = true; //取最小时，需要判断 是否是 第一次出现 cnt<2 的情况，防止自身异或
        for (int i = len - 1; i >= 0; i--) {
            int x = (s >> i) & 1;
            if(large) x ^= 1;
            if (!nxt[now][x] || (!large && st && cnt[nxt[now][x]] < 2)) {
                st = false;
                now = nxt[now][x ^ 1];
            } else {
                ans += (large ? 1 : -1) * (1 << i);
                now = nxt[now][x];
            }
        }
        return ans;
    }
} trie01;

