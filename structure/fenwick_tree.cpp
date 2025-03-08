#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

template<class Info = int>
struct FenwickTree {
    int n;
    vector<Info> info;
    FenwickTree() : n(0) {}
    explicit FenwickTree(int _n, Info _v = Info()) : info(_n + 1, _v), n(_n) {}
    inline static int lowbit(int x) { return x & (-x); }
    void pointUpdate(int pos, Info _info) {
        for (int i = pos; i <= n; i += lowbit(i)) info[i] = info[i] + _info;
    }
    Info rangeQuery(int r) {
        Info ans{};
        for (int i = r; i > 0; i -= lowbit(i)) ans = ans + info[i];
        return ans;
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(r) - rangeQuery(l - 1);
    }
    Info lowerBound(int x) {
        int pos = 0, t = 0;
        for (int j = 20; j >= 0; j--) {
            if (pos + (1 << j) <= n && t + info[pos + (1 << j)] <= x)
                pos += (1 << j), t += info[pos];
        }
        return pos;
    }
};

struct Info{
    int val = 0;
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.val = a.val + b.val;
    return c;
}

Info operator-(const Info &a, const Info &b) {
    return a + Info{-b.val};
}