#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct SHORTEST_PATH {
    struct SINGLE { //单源最短路 & 链式前向星
        int n, m, dist[N], h[N], w[N], e[N], ne[N], idx;
        bool st[N];
        void add(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }
        void init(int tn, int tm) { n = tn, m = tm, memset(h, -1, sizeof h); }
        void dijkstra(int start) { //堆优化 Dijkstra
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
            memset(dist, 0x3f, sizeof dist);
            dist[start] = 0, q.emplace(0, start);
            while (!q.empty()) {
                auto [d, v] = q.top(); q.pop();
                if (st[v]) continue;
                st[v] = true;
                for (int i = h[v]; i != -1; i = ne[i]) {
                    int to = e[i];
                    if (dist[to] > d + w[i]) dist[to] = d + w[i], q.emplace(dist[to], to);
                }
            }
        }
        void spfa(int start) { //SPFA
            queue<int> q;
            memset(dist, 0x3f, sizeof dist);
            dist[start] = 0, st[start] = true, q.emplace(start);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                st[v] = false;
                for (int i = h[v]; i != -1; i = ne[i]) {
                    int to = e[i];
                    if (dist[to] > dist[v] + w[i]) { //松弛
                        dist[to] = dist[v] + w[i];
                        if (!st[to]) q.emplace(to), st[to] = true;
                    }
                }
            }
        }
        bool spfaNegative() { //SPFA判负环
            queue<int> q;
            vector<int> cnt(n + 1);
            for (int i = 1; i <= n; i++) st[i] = true, q.emplace(i);
            while (q.size()) {
                int v = q.front(); q.pop();
                st[v] = false;
                for (int i = h[v]; i != -1; i = ne[i]) {
                    int to = e[i];
                    if (dist[to] > dist[v] + w[i]) {
                        dist[to] = dist[v] + w[i], cnt[to] = cnt[v] + 1;
                        if (cnt[to] >= n) return true;
                        if (!st[to]) q.emplace(to), st[to] = true;
                    }
                }
            }
            return false;
        }
    } sg;
    struct MULTI { //多源最短路
        int n, m, dist[N][N];
        void init(int tn, int tm) {
            n = tn, m = tm;
            for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) dist[i][j] = i == j ? 0 : inf;
        }
        void add(int u, int v, int w) { dist[u][v] = min(dist[u][v], w); }
        void floyd() { for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); }
        bool check(int u, int v) { return dist[u][v] < inf / 2; }
    } mt;
} sp;