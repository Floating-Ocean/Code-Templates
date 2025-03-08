#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e3 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

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

struct MIN_SPAN_TREE {
    struct KRUSKAL {
        int n, m, idx;
        struct Edge{
            int a, b, w;
            bool operator< (const Edge &W)const{ return w < W.w; }
        } edges[M];
        void init(int tn, int tm){ n = tn, m = tm, dsu.init(n); }
        void add(int u, int v, int w) { edges[idx ++] = {u, v, w}; }
        int kruskal(){
            sort(edges, edges + m);
            int res = 0, cnt = 0;
            for (int i = 0; i < m; i ++){
                auto [a, b, w] = edges[i];
                a = dsu.find(a), b = dsu.find(b);
                if (a != b) dsu.unite(a, b), res += w, cnt ++;
            }
            if (cnt < n - 1) return inf;
            return res;
        }
    } kruskal;
    struct PRIM {
        int n, m, e[N][N], dist[N];
        bool st[N];
        void init(int tn, int tm) {
            n = tn, m = tm;
            for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) e[i][j] = inf;
        }
        void add(int u, int v, int w) { e[u][v] = min(e[u][v], w); }
        int prim(){
            memset(dist, 0x3f, sizeof dist);
            int res = 0;
            for (int i = 0; i < n; i ++){
                int t = -1;
                for (int j = 1; j <= n; j ++) if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
                if (i && dist[t] == inf) return inf;
                if (i) res += dist[t];
                st[t] = true;
                for (int j = 1; j <= n; j ++) dist[j] = min(dist[j], e[t][j]);
            }
            return res;
        }
    } prim;
} mst;
