#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct MATH {
    static __int128 qp(__int128 x, __int128 y, __int128 m = mod) {
        static __int128 ans;
        ans = 1, x %= m;
        for (; y; y >>= 1, x = x * x % m) if (y & 1) ans = ans * x % m;
        return ans;
    }
    int inv(int n, int m = mod) { return qp(n, m - 2, m); }
} math;

struct Ma {
    int a[40][40]; //开太大会喜逢爆内存和汇编代码
    int n, m, _mod;
    bool rev;
    Ma(int _n, int _m, int _md): n(_n), m(_m), _mod(_md) {}
};

namespace Mat {
    bool enableMod = true;
    int md(int x, int mod) { return enableMod ? (x % mod + mod) % mod : x; }
    void offMod() { enableMod = false; }
    Ma Ma_E(Ma o) {
        Ma res(o.n, o.m, o._mod);
        for(int i=1;i<=min(o.n,o.m);i++) res.a[i][i] = 1;
        return res;
    }
    Ma Ma_add(Ma p, Ma q) {
        Ma res(p.n, p.m, p._mod);
        for (int i = 1; i <= p.n; i++) for (int j = 1; j <= p.m; j++) res.a[i][j] = md(p.a[i][j] + q.a[i][j], p._mod);
        return res;
    }
    Ma Ma_minus(Ma p, Ma q) {
        Ma res(p.n, p.m, p._mod);
        for (int i = 1; i <= p.n; i++) for (int j = 1; j <= p.m; j++) res.a[i][j] = md(p.a[i][j] - q.a[i][j], p._mod);
        return res;
    }
    Ma Ma_mul(Ma p, Ma q) {
        Ma res(p.n, q.m, p._mod);
        for (int i = 1; i <= p.n; i++) for (int j = 1; j <= q.m; j++) {
                int sum = 0;
                for (int k = 1; k <= p.m; k++) sum = md(sum + md(p.a[i][k] * q.a[k][j], p._mod), p._mod);
                res.a[i][j] = sum;
            }
        return res;
    }
    Ma Ma_inv(Ma p) { //取逆
        Ma aug(p.n, p.n << 1, p._mod);
        for (int i = 1; i <= p.n; i++) { //构造增广矩阵(P,E)，变换得(E,P^-1)
            for (int j = 1; j <= p.n; j++) aug.a[i][j] = p.a[i][j];
            aug.a[i][p.n + i] = 1;
        }
        bool check = true;
        for (int i = 1, r; i <= p.n; i++) { //高斯消元
            r = i;
            for (int j = i + 1; j <= p.n; j++) if (aug.a[j][i] > aug.a[r][i]) r = j;
            if (r != i) swap(aug.a[i], aug.a[r]);
            if (!aug.a[i][i]) {
                check = false;
                break;
            }
            int di = math.inv(aug.a[i][i]);
            for (int k = 1; k <= p.n; k++) {
                if (k == i) continue;
                int t = md(aug.a[k][i] * di, p._mod);
                for (int j = i; j <= (p.n << 1); j++) aug.a[k][j] = md(aug.a[k][j] - md(t * aug.a[i][j], p._mod), p._mod);
            }
            for (int j = 1; j <= (p.n << 1); j++) aug.a[i][j] = md(aug.a[i][j] * di, p._mod);
        }
        Ma res(p.n, p.n, p._mod); //导出右边一半
        res.rev = check;
        if(res.rev) for (int i = 1; i <= p.n; i++) for (int j = p.n + 1; j <= (p.n << 1); j++) res.a[i][j - p.n] = aug.a[i][j];
        return res;
    }
    Ma Ma_div(Ma p, Ma q) { //右乘上p逆
        return Ma_mul(p, Ma_inv(q));
    }
    // 矩阵快速幂
    static Ma Ma_qp(Ma p, int k) {
        Ma ans(p.n, p.m, p._mod);
        for(int i=1;i<=p.n;i++) ans.a[i][i] = 1; //单位矩阵
        if(k <= 0) return ans;
        Ma base = Ma_mul(ans, p);
        while (k > 0) {
            if (k & 1) ans = Ma_mul(ans, base);
            base = Ma_mul(base, base);
            k >>= 1;
        }
        return ans;
    }
} using namespace Mat;