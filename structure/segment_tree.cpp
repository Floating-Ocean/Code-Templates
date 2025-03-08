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
    //param: predicate function
    template<class Func>
    int findFirst(int p, int l, int r, int x, int y, Func pred){
        if(l > y || r < x || !pred(info[p])){
            return -1;
        }
        if(l == r){
            return l;
        }
        int mid = (l + r) >> 1;
        push(p, l, r);
        int ans = findFirst(2 * p, l, mid, x, y, pred);
        if(ans == -1){
            ans = findFirst(2 * p + 1, mid + 1, r, x, y, pred);
        }
        return ans;
    }
    template<class Func>
    int findFirst(int l, int r, Func pred){
        return findFirst(1, 1, n, l, r, pred);
    }
    template<class Func>
    int findLast(int p, int l, int r, int x, int y, Func pred){
        if(l > y || r < x || !pred(info[p])){
            return -1;
        }
        if(l == r){
            return l;
        }
        int mid = (l + r) >> 1;
        push(p, l, r);
        int ans = findLast(2 * p + 1, mid + 1, r, x, y, pred);
        if(ans == -1){
            ans = findLast(2 * p, l, mid, x, y, pred);
        }
        return ans;
    }
    template<class Func>
    int findLast(int l, int r, Func pred){
        return findLast(1, 1, n, l, r, pred);
    }
};