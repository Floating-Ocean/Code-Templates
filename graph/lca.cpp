#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> adj(n + 1);
    for(int i=1;i<n;i++){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v), adj[v].emplace_back(u);
    }
    vector<vector<int>> fa(21, vector<int>(n + 1));
    vector<int> dep(n + 1);
    auto dfs = [&](auto dfs, int x, int p) -> void{
        fa[0][x] = p, dep[x] = dep[p] + 1;
        for(int i=1;i<=20;i++){
            fa[i][x] = fa[i - 1][fa[i - 1][x]];
        }
        for(auto y : adj[x]){
            if(y == p) continue;
            dfs(dfs, y, x);
        }
    };
    dfs(dfs, s, 0);
    auto lca = [&](int x, int y) {
        if (dep[x] > dep[y]) swap(x, y);
        int dif = dep[y] - dep[x];
        for (int j = 0; dif > 0; j++, dif >>= 1) {
            if (dif & 1) y = fa[j][y];
        }
        if (y == x) return x;
        for (int i = 20; i >= 0; i--) {
            if (fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
        }
        return fa[0][x];
    };
    while(m --){
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
}