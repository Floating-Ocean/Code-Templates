#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

set<pair<int, int>> E; //割边

struct EBCC { //割边与割边缩点
    int n;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, bel;
    int now, cnt;

    explicit EBCC(){}
    explicit EBCC(int n) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        now = cnt = 0;
    }

    void addEdge(int u, int v) {
        adj[u].emplace_back(v), adj[v].emplace_back(u);
    }

    vector<int> work() {
        auto dfs = [&](auto self, int x, int p) -> void{
            stk.push_back(x);
            dfn[x] = low[x] = now ++;
            for(auto &y : adj[x]) {
                if(y == p) continue;
                if(dfn[y] == -1) {
                    E.emplace(x, y);
                    self(self, y, x);
                    low[x] = min(low[x], low[y]);
                }else if(bel[y] == -1) {
                    E.emplace(x, y);
                    low[x] = min(low[x], dfn[y]);
                }
            }
            if(dfn[x] == low[x]) {
                int y;
                do {
                    y = stk.back();
                    stk.pop_back();
                    bel[y] = cnt;
                } while(y != x);
                cnt ++;
            }
        };
        dfs(dfs, 0, -1);
        return bel;
    }

    struct Graph {
        int n;
        vector<pair<int, int>> edges;
        vector<int> siz, cnt_e;
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnt_e.resize(cnt);
        for(int i=0;i<n;i++) {
            g.siz[bel[i]] ++;
            for(auto &j : adj[i]) {
                if(bel[i] < bel[j]) {
                    g.edges.emplace_back(bel[i], bel[j]);
                }else if(i < j) {
                    g.cnt_e[bel[i]] ++;
                }
            }
        }
        return g;
    }
};