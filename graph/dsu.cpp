#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct DSU {
    vector<int> pa, siz;
    void init(int n) { pa = vector<int>(n + 1), siz = vector<int>(n + 1, 1), iota(pa.begin(), pa.end(), 0); }
    int find(int x) { while(x != pa[x]) x = pa[x] = pa[pa[x]]; return x; }
    bool unite(int u, int v) {
        int f1 = find(u), f2 = find(v);
        if (f1 == f2) return false;
        siz[f1] += siz[f2];
        pa[f2] = f1;
        return true;
    }
    int size(int x){ return siz[find(x)]; }
} dsu;

struct WEIGHT_DSU {
    vector<int> pa, w;
    void init(int n) { pa = vector<int>(n + 1), w = vector<int>(n + 1), iota(pa.begin(), pa.end(), 0); }
    int find(int x) { return pa[x] == x ? x : (pa[x] = find(pa[x]), w[x] += w[pa[x]], pa[x]); }
    bool unite(int u, int v, auto upd) {
        int f1 = find(u);
        int f2 = find(v);
        if (f1 != f2) pa[f2] = f1;
        upd(w, f1, f2);
        return f1 != f2;
    }
} w_dsu;