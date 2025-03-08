#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e3 + 10, M = 2e6 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct DINIC { //下标[1,n] 循环跑 bfs, dfs(递推实现) 包含向前弧优化 复杂度 O(m*(n^2))
    struct Edge {
        int to, nxt, cap, flow; //链式前向星，容量，流的大小
    } edge[M];
    int tot, head[N];
    void init() { tot = 2, memset(head, -1, sizeof head); }
    void add(int u, int v, int w, int rw = 0) { //residual 反向边 w
        edge[tot].to = v, edge[tot].cap = w, edge[tot].flow = 0, edge[tot].nxt = head[u], head[u] = tot++;
        edge[tot].to = u, edge[tot].cap = rw, edge[tot].flow = 0, edge[tot].nxt = head[v], head[v] = tot++;
    }
    int Q[N];
    int dep[N], cur[N], sta[N];
    bool bfs(int s, int t, int n) { //判是否还存在一条从s到t的流
        int front = 0, tail = 0;
        memset(dep, -1, (sizeof dep[0]) * (n + 1));
        dep[s] = 0;
        Q[tail++] = s;
        while (front < tail) {
            int u = Q[front++];
            for (int i = head[u]; i != -1; i = edge[i].nxt) {
                int v = edge[i].to;
                if (edge[i].cap > edge[i].flow && dep[v] == -1) {
                    dep[v] = dep[u] + 1; //建图
                    if (v == t) return true;
                    Q[tail++] = v;
                }
            }
        }
        return false;
    }
    int dinic(int s, int t, int n) {
        int maxFlow = 0;
        while (bfs(s, t, n)) {
            for (int i = 1; i <= n; i++) cur[i] = head[i]; //当前弧优化
            int u = s, tail = 0;
            while (cur[s] != -1) {
                if (u == t) {
                    int tp = inf; //这条流的瓶颈
                    for (int i = tail - 1; i >= 0; i--) tp = min(tp, edge[sta[i]].cap - edge[sta[i]].flow);
                    maxFlow += tp;
                    for (int i = tail - 1; i >= 0; i--) {
                        edge[sta[i]].flow += tp; //构建反向边，用于贪心反悔
                        edge[sta[i] ^ 1].flow -= tp;
                        if (edge[sta[i]].cap - edge[sta[i]].flow == 0) tail = i;
                    }
                    u = edge[sta[tail] ^ 1].to;
                } else if (cur[u] != -1 && edge[cur[u]].cap > edge[cur[u]].flow && dep[u] + 1 == dep[edge[cur[u]].to]) { //保证这条边能走，且是从i层流到i+1层
                    sta[tail++] = cur[u]; //sta为路径
                    u = edge[cur[u]].to;
                } else {
                    while (u != s && cur[u] == -1) u = edge[sta[--tail] ^ 1].to; //回退
                    cur[u] = edge[cur[u]].nxt;
                }
            }
        }
        return maxFlow;
    }
} dinic;