#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct TwoSat {
    int n;
    vector<vector<int>> adj;
    vector<int> ans;

    explicit TwoSat(int n) : n(n), adj(2 * n), ans(n) {}

    void addClause(int u, bool f, int v, bool g) {
        adj[2 * u + !f].emplace_back(2 * v + g);
        adj[2 * v + !g].emplace_back(2 * u + f);
    }

    bool check() {
        vector<int> bel(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        vector<int> stk;
        int now = 0, cnt = 0;
        auto tarjan = [&](auto self, int x) -> void {
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
        for(int i=0;i<2*n;i++) {
            if(dfn[i] == -1) tarjan(tarjan, i);
        }
        for(int i=0;i<n;i++) {
            if(bel[i * 2] == bel[i * 2 + 1]) return false;
            ans[i] = bel[2 * i] > bel[2 * i + 1];
        }
        return true;
    }

    vector<int> answer() {
        return ans;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(4, vector<int>(n + 1));
    for(int i=1;i<=3;i++) {
        for(int j=1;j<=n;j++) {
            cin >> a[i][j];
        }
    }
    TwoSat ts(n);
    for(int j=1;j<=n;j++) {
        for(int x=2;x<=3;x++) {
            for(int y=1;y<x;y++) {
                //添加条件: x,y不同时为负
                ts.addClause(abs(a[x][j]) - 1, a[x][j] > 0, abs(a[y][j]) - 1, a[y][j] > 0);
            }
        }
    }
    cout << (ts.check() ? "YES\n" : "NO\n");
}