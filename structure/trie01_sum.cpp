#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct TRIE01 {
    int nxt[N * 30][2], idx, sum[N * 30], len, root;
    void init(int k) { len = k, memset(nxt, 0, (sizeof nxt[0]) * (idx + 1)), memset(sum, 0, (sizeof sum[0]) * (idx + 1)), idx = 1, root = idx ++; }
    void update(int x, int val){
        int now = root;
        for(int i= len - 1; i >= 0;i--) {
            int p = (x >> i) & 1;
            if(!nxt[now][p]) nxt[now][p] = idx ++;
            now = nxt[now][p];
            sum[now] = (sum[now] + val) % mod;
        }
    }
    int query(int s, int k){ //查找满足 x xor s <= k 的 sum[x]
        int now = root, ans = 0;
        for (int i = len - 1; i >= 0; i--) {
            int x = (s >> i) & 1;
            if((k >> i) & 1) { //k该位反选0，低位就可任意选
                if(nxt[now][x]) ans = (ans + sum[nxt[now][x]]) % mod;
                now = nxt[now][x ^ 1];
            }else now = nxt[now][x];
        }
        ans = (ans + sum[now]) % mod; // ==k
        return ans;
    }
} trie01;

