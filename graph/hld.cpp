#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct HLD { //树链剖分
    int n;
    vector<int> siz, top, dep, parent, in, out, seq;
    vector<vector<int>> adj;
    vector<vector<int>> chain;
    int cur;

    explicit HLD() {}
    explicit HLD(int n) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
        chain.resize(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    void work(int root = 0, int lim = -1) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        chain[root].emplace_back(root);
        dfs1(root, lim);
        dfs2(root, lim);
    }
    void dfs1(int x, int lim) { //保证adj中不会有其父节点，且x的重儿子在adj[x][0]（深度大于lim不处理）
        if(parent[x] != -1) {
            adj[x].erase(find(adj[x].begin(), adj[x].end(), parent[x]));
        }

        siz[x] = 1;
        if(dep[x] == lim) return;

        for(auto &y : adj[x]) {
            parent[y] = x;
            dep[y] = dep[x] + 1;
            dfs1(y, lim);
            siz[x] += siz[y];
            if(siz[y] > siz[adj[x][0]]) swap(y, adj[x][0]);
        }
    }
    void dfs2(int x, int lim) { //x的子树dfn的范围 [in[x], out[x])
        in[x] = cur ++;
        seq[in[x]] = x;

        if(dep[x] != lim) {
            for(auto &y : adj[x]) {
                top[y] = y == adj[x][0] ? top[x] : y;
                chain[top[y]].emplace_back(y);
                dfs2(y, lim);
            }
        }

        out[x] = cur;
    }
    int lca(int u, int v) {
        while(top[u] != top[v]) { //深度大的向上跳到上一个链
            if(dep[top[u]] > dep[top[v]]) u = parent[top[u]];
            else v = parent[top[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    int jump(int u, int k) { //向上跳k
        if(dep[u] < k) return -1;

        int d = dep[u] - k;
        while(dep[top[u]] > d) u = parent[top[u]];

        return seq[in[u] - dep[u] + d];
    }

    bool isAncestor(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }

    int rootedParent(int x, int root) { //root的所有子树中，x所在的子树的根节点
        if(x == root) return root;
        if(!isAncestor(root, x)) return parent[root]; //父亲节点即为所求子树的根节点
        auto it = upper_bound(adj[root].begin(), adj[root].end(), x, [&](int u, int v) {
            return in[u] < in[v];
        }) - 1;
        return *it;
    }

    int rootedSize(int x, int root) { //root的所有子树中，去除x所在的子树后的大小
        if(x == root) return n;
        if(!isAncestor(root, x)) return siz[root];
        return n - siz[rootedParent(x, root)];
    }

    int rootedLca(int a, int b, int root) { //以root为根时，LCA(a,b)
        return lca(a, b) ^ lca(a, root) ^ lca(b, root);
    }
};