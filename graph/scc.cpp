#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct SCC { //强连通分量缩点
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int now, cnt;

    explicit SCC() {}
    explicit SCC(int n) {
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
        adj[u].emplace_back(v);
    }

    vector<int> work() {
        auto tarjan = [&](auto self, int x) -> void{
            stk.push_back(x);
            dfn[x] = low[x] = now ++;
            for(auto &y : adj[x]) {
                if(dfn[y] == -1) {
                    self(self, y);
                    low[x] = min(low[x], low[y]);
                }else if(bel[y] == -1) {
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
        for(int i=0;i<n;i++) {
            if(dfn[i] == -1) tarjan(tarjan, i);
        }
        return bel;
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    SCC scc(n);
    for(int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u --, v --;
        adj[u].emplace_back(v);
        scc.addEdge(u, v);
    }
    auto bel = scc.work();
    vector<int> dp(n, -1);
    for(int i=0;i<n;i++) {
        if(dp[i] != -1) continue;
        queue<int> q;
        q.emplace(i);
        dp[i] = 0;
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(auto &y : adj[x]) {
                if(dp[y] == -1 && bel[x] == bel[y]) {
                    q.emplace(y);
                    dp[y] = dp[x] + 1;
                }
            }
        }
    }
    int ans = 0, cnt = scc.cnt;
    vector<vector<int>> v(cnt); //缩点
    for(int i=0;i<n;i++) {
        v[bel[i]].emplace_back(i);
    }
    for(auto &a : v) {
        int g = 0;
        for(auto &x : a) {
            for(auto &y : adj[x]) {
                if(bel[x] == bel[y]) {
                    g = gcd(g, dp[x] + 1 - dp[y]);
                }
            }
        }
        if(g == 0) continue;
        vector<int> sz(g);
        for(auto &x : a) sz[dp[x] % g] ++;
        if(k % g == 0) {
            ans += a.size();
            for(int i=0;i<g;i++) ans += sz[i] * (sz[i] - 1) / 2;
        }else if(k * 2 % g == 0) {
            for(int i=0;i<g/2;i++) {
                ans += sz[i] * sz[i + g / 2];
            }
        }
    }
    cout << ans << '\n';
}