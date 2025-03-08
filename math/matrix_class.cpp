#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

//矩阵规模过大时不宜使用
template<typename T>
struct Matrix{
    vector<vector<T>> a;
    int n, m, _mod;
    bool rev = true; //在求逆的时候，标记是否发现无法求逆（调用 "~本身"后，在返回的矩阵中访问此参数即可）
    Matrix(int _n, int _m, int _md = mod): n(_n), m(_m), _mod(_md){ a = vector<vector<T>>(_n + 1, vector<T>(_m + 1)); }
    Matrix<T> E(){
        Matrix<T> res(n, m, _mod);
        for(int i=1;i<=min(n,m);i++) res[i][i] = 1;
        return res;
    }
    vector<T> & operator[](const int x) { return a[x]; }
    Matrix<T> operator+(const Matrix<T> &p) const {
        Matrix<T> res(n, m, _mod);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) res[i][j] = md(a[i][j] + p.a[i][j]);
        return res;
    }
    Matrix<T> operator-(const Matrix<T> &p) const {
        Matrix<T> res(n, m, _mod);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) res[i][j] = md(a[i][j] - p.a[i][j]);
        return res;
    }
    Matrix<T> operator*(const Matrix<T> &p) const {
        Matrix<T> res(n, p.m, _mod);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= p.m; j++) {
                int sum = 0;
                for (int k = 1; k <= m; k++) sum = md(sum + md(a[i][k] * p.a[k][j]));
                res[i][j] = sum;
            }
        return res;
    }
    Matrix<T> operator ~() const { //取逆
        Matrix<T> aug(n, n << 1, _mod);
        for (int i = 1; i <= n; i++) { //构造增广矩阵(P,E)，变换得(E,P^-1)
            for (int j = 1; j <= n; j++) aug[i][j] = a[i][j];
            aug[i][n + i] = 1;
        }
        bool check = true;
        for (int i = 1, r; i <= n; i++) { //高斯消元
            r = i;
            for (int j = i + 1; j <= n; j++) if (aug[j][i] > aug[r][i]) r = j;
            if (r != i) swap(aug[i], aug[r]);
            if (!aug[i][i]) {
                check = false;
                break;
            }
            T di = inv(aug[i][i]);
            for (int k = 1; k <= n; k++) {
                if (k == i) continue;
                T p = md(aug[k][i] * di);
                for (int j = i; j <= (n << 1); j++) aug[k][j] = md(aug[k][j] - md(p * aug[i][j]));
            }
            for (int j = 1; j <= (n << 1); j++) aug[i][j] = md(aug[i][j] * di);
        }
        Matrix<T> res(n, n, _mod); //导出右边一半
        res.rev = check;
        if(res.rev) for (int i = 1; i <= n; i++) for (int j = n + 1; j <= (n << 1); j++) res[i][j - n] = aug[i][j];
        return res;
    }
    Matrix<T> operator/(const Matrix<T> &p) const { //右乘上p逆
        Matrix<T> me = *this, inv = ~p;
        return me * inv;
    }
    Matrix<T> & operator+=(const Matrix<T> &p) { a = ((*this) + p).a; return *this; }
    Matrix<T> & operator-=(const Matrix<T> &p) { a = ((*this) - p).a; return *this; }
    Matrix<T> & operator*=(const Matrix<T> &p) { a = ((*this) * p).a; return *this; }
    Matrix<T> & operator/=(const Matrix<T> &p) { a = ((*this) / p).a; return *this; }
    // 矩阵快速幂
    Matrix<T> qp(int p) {
        Matrix<T> ans(n, m, _mod);
        for(int i=1;i<=n;i++) ans[i][i] = 1; //单位矩阵
        if(p <= 0) return ans;
        Matrix<T> base = ans;
        base *= *this;
        while (p > 0) {
            if (p & 1) ans *= base;
            base *= base;
            p >>= 1;
        }
        return ans;
    }
    void offMod(){ enableMod = false; } //关掉默认取模
private:
    bool enableMod = true;
    inline T inv(T x) const { return enableMod ? doInv(x) : 1 / x; }
    inline int doInv(int x) const { return mqp(x, _mod - 2); }
    inline T md(T x) const { return enableMod ? doMod(x) : x; }
    inline int doMod(int x) const { return (x % _mod + _mod) % _mod; }
    inline int mqp(int x, int y) const {
        static int ans;
        ans = 1, x %= _mod;
        for (; y; y >>= 1, x = x * x % _mod) if (y & 1) ans = ans * x % _mod;
        return ans;
    }
};
using mi = Matrix<int>;
using md = Matrix<double>;