#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e3 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct MIN_CIRCUIT { //无向图最小环
    int n, m, dist[N][N], e[N][N], pre[N][N];
    void init(int tn, int tm) {
        n = tn, m = tm;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) e[i][j] = dist[i][j] = inf, pre[i][j] = i;
    }
    void add(int u, int v, int w) { dist[u][v] = e[u][v] = min(dist[u][v], w); }
    pair<int, vector<int> > floyd() {
        vector<int> path;
        int ans = inf;
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i < n; i++)
                for (int j = i + 1; j < k; j++){
                    if(e[j][k] >= inf || e[k][i] >= inf) continue;
                    if(dist[i][j] + e[j][k] + e[k][i] < ans){
                        ans = dist[i][j] + e[j][k] + e[k][i];
                        int t = j;
                        path.clear();
                        path.emplace_back(j);
                        while(pre[i][t] != i){
                            path.emplace_back(pre[i][t]);
                            t = pre[i][t];
                        }
                        path.emplace_back(i), path.emplace_back(k);
                    }
                }
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++) {
                    if(dist[i][k] + dist[k][j] < dist[i][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pre[i][j] = pre[k][j];
                    }
                }
        }
        return {ans, path};
    }
    bool check(int u, int v) { return dist[u][v] < inf / 2; }
} mc;