#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

template<class Info>
struct SparseTable {
    int n;
    vector<vector<Info>> info;
    vector<int> lg;
    SparseTable() : n(0) {}
    void initLg() {
        lg = vector<int>(n + 1, -1);
        for(int i=1;i<=n;i++) lg[i] = lg[i / 2] + 1;
    }
    explicit SparseTable(int _n, vector<Info> _info) : n(_n) {
        initLg();
        info = vector<vector<Info>>(n + 1, vector<Info>(lg[n] + 1));
        for(int i=1;i<=n;i++) info[i][0] = _info[i];
        for(int i=1;i<=lg[n];i++){
            for(int j=1;j+(1ll<<(i-1))<=n;j++){
                info[j][i] = info[j][i - 1] + info[j + (1ll << (i - 1))][i - 1];
            }
        }
    }
    Info rangeQuery(int l, int r) {
        int len = lg[r - l + 1];
        return info[l][len] + info[r - (1ll << len) + 1][len];
    }
};

struct Info{
    int val = 0;
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.val = max(a.val, b.val); //RMQ
    return c;
}