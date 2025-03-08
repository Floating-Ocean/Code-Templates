#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

//单点修改线段树
template<class Info>
struct SegmentTree {
    int n;
    vector<Info> info;
    SegmentTree() : n(0) {}
    explicit SegmentTree(int _n, Info _v = Info()) {
        init(_n, _v);
    }
    template<class T>
    explicit SegmentTree(vector<T> _init) {
        init(_init);
    }
    void init(int _n, Info _v = Info()) {
        init(vector(_n, _v));
    }
    template<class T>
    void init(vector<T> _init) {
        n = _init.size();
        info.assign(4 << __lg(n), Info());
        auto build = [&](auto self, int p, int l, int r) -> void{
            if(r - l == 1){
                info[p] = _init[l];
                return;
            }
            int mid = (l + r) >> 1;
            self(self, 2 * p, l, mid);
            self(self, 2 * p + 1, mid, r);
            pull(p);
        };
        build(build, 1, 0, n);
    }
    void pull(int p){
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v){
        if(r - l == 1){
            info[p] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if(x < mid) modify(2 * p, l, mid, x, v);
        else modify(2 * p + 1, mid, r, x, v);
        pull(p);
    }
    void modify(int p, const Info &v){
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y){
        if(l >= y || r <= x){
            return Info();
        }
        if(l >= x && r <= y){
            return info[p];
        }
        int mid = (l + r) >> 1;
        return rangeQuery(2 * p, l, mid, x, y) + rangeQuery(2 * p + 1, mid, r, x, y);
    }
    Info rangeQuery(int l, int r){
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Info {
    int mn = inf, mx = -inf;
    unsigned int sum = 0;
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum ^ b.sum;
    c.mn = min(a.mn, b.mn);
    c.mx = max(a.mx, b.mx);
    return c;
}