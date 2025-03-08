#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct SECOND_SHORTEST_PATH {
    int n, m, dist[N], dist2[N], h[N], w[N], e[N], ne[N], idx;
    bool st[N];
    void add(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }
    void init(int tn, int tm) { n = tn, m = tm, memset(h, -1, sizeof h); }
    void dijkstra(int start) { //堆优化 Dijkstra
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        memset(dist, 0x3f, sizeof dist);
        memset(dist2, 0x3f, sizeof dist2);
        dist[start] = 0, q.emplace(0, start);
        while (!q.empty()) {
            auto [d, v] = q.top();
            q.pop();
            if (dist2[v] < d) continue;
            for (int i = h[v]; i != -1; i = ne[i]) {
                int to = e[i];
                if (dist[to] > d + w[i]) dist2[to] = dist[to], dist[to] = d + w[i], q.emplace(dist[to], to);
                if (dist[to] < d + w[i] && dist2[to] > d + w[i]) dist2[to] = d + w[i], q.emplace(dist2[to], to);
            }
        }
    }
} sp2;