#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

//每个线段的信息，以及标记
template<class Info, class Tag>
struct SegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    SegmentTree() : n(0) {}
    SegmentTree(int _n, Info _v = Info()) {
        init(_n, _v);
    }
    template<class T>
    SegmentTree(vector<T> _init) {
        init(_init);
    }
    void init(int _n, Info _v = Info()) {
        init(vector(_n, _v));
    }
    template<class T>
    void init(vector<T> _init) {
        n = _init.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        auto build = [&](auto build, int p, int l, int r) -> void{
            if(l == r){
                info[p] = _init[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(build, 2 * p, l, mid);
            build(build, 2 * p + 1, mid + 1, r);
            pull(p);
        };
        build(build, 1, 1, n);
    }
    void pull(int p){
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, int l, int r, const Tag &v){
        info[p].apply(v, l, r);
        tag[p].apply(v);
    }
    void push(int p, int l, int r){
        int mid = (l + r) >> 1;
        apply(2 * p, l, mid, tag[p]);
        apply(2 * p + 1, mid + 1, r, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v){
        if(l == r){
            info[p] = v;
            return;
        }
        int mid = (l + r) >> 1;
        push(p, l, r);
        if(x < mid) modify(2 * p, l, mid, x, v);
        else modify(2 * p + 1, mid + 1, r, x, v);
        pull(p);
    }
    void modify(int p, const Info &v){
        modify(1, 1, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y){
        if(l > y || r < x){
            return Info();
        }
        if(l >= x && r <= y){
            return info[p];
        }
        int mid = (l + r) >> 1;
        push(p, l, r);
        return rangeQuery(2 * p, l, mid, x, y) + rangeQuery(2 * p + 1, mid + 1, r, x, y);
    }
    Info rangeQuery(int l, int r){
        return rangeQuery(1, 1, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if(l > y || r < x) return;
        if(l >= x && r <= y){
            apply(p, l, r, v);
            return;
        }
        int mid = (l + r) >> 1;
        push(p, l, r);
        rangeApply(2 * p, l, mid, x, y, v);
        rangeApply(2 * p + 1, mid + 1, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v){
        return rangeApply(1, 1, n, l, r, v);
    }
};

struct Tag {
    int add = 0, mul = 1;

    void apply(const Tag &t) & {
        add = add * t.mul + t.add;
        mul = mul * t.mul;
    }
};

struct Info {
    int sum = 0, mx = -inf, mn = inf;

    void apply(const Tag &t, const int l, const int r) & {
        sum = sum * t.mul + t.add * (r - l + 1);
        mx = mx * t.mul + t.add;
        mn = mn * t.mul + t.add;
    }
};

Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.mx = max(a.mx, b.mx);
    c.mn = min(a.mn, b.mn);
    return c;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Info> init(n + 1);
    for(int i=1;i<=n;i++) {
        cin >> init[i].sum;
        init[i].mx = init[i].mn = init[i].sum;
    }
    SegmentTree<Info, Tag> seg(init);
    while(m --){
        char op;
        cin >> op;
        if(op == 'M'){
            int l, r;
            cin >> l >> r;
            cout << seg.rangeQuery(l, r).mn << '\n';
        }else if(op == 'P') {
            int l, r, x;
            cin >> l >> r >> x;
            seg.rangeApply(l, r, {x, 1});
        }else{
            int l, r;
            cin >> l >> r;
            cout << seg.rangeQuery(l, r).sum << '\n';
        }
    }
}