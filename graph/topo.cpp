#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct TOPO {
    int n, m;
    int h[N], e[N], ne[N], idx; //链式前向星
    int d[N];
    void add(int a, int b){
        e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
    }
    bool topoSort() { //拓扑排序
        queue<int> q;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (!d[i])
                q.push(i);
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            cnt ++;
            for (int i = h[t]; i != -1; i = ne[i]){
                int j = e[i];
                if (-- d[j] == 0) q.push(j);
            }
        }
        return cnt == n;
    }
} topo;