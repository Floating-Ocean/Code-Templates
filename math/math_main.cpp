#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct Math {
//------基础------
    static __int128 qp(__int128 x, __int128 y, const __int128 m = mod) {
        static __int128 ans;
        ans = 1, x %= m;
        for (; y; y >>= 1, x = x * x % m) if (y & 1) ans = ans * x % m;
        return ans;
    }
    static int inv(const int n, const int m = mod) { return (int) qp(n, m - 2, m); }
    template<class T> static T ex_sqrt(T x) { //返回精度更高的sqrt
        T sqrtX = sqrt(x) - 1;
        while (sqrtX + 1 <= x / (sqrtX + 1)) ++ sqrtX;
        return sqrtX;
    }
//------预处理------
    //线性求阶乘，逆元，阶乘逆元
    static void get_fact_inv(const int n, int fac[], int inv[], int fac_inv[], const int p = mod) {
        fac[0] = fac_inv[0] = inv[0] = fac[1] = fac_inv[1] = inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            fac[i] = fac[i - 1] * i % p;
            inv[i] = (p - p / i * inv[p % i] % p) % p; //线性求逆元
            fac_inv[i] = fac_inv[i - 1] * inv[i] % p;
        }
    }
	//线性筛求积性函数
    static void sieve_mul_func(const int n, bool not_pri[], int pr[], int &cnt, const auto &&new_pri, const auto &&stop, const auto &&on) {
        for (int i = 2; i <= n; i ++) {
            if (!not_pri[i]) pr[cnt++] = i, new_pri(i);
            for (int j = 0; j < cnt && i * pr[j] <= n; j ++) {
                not_pri[i * pr[j]] = true;
                if (i % pr[j] == 0) {
                    stop(i, pr[j]);
                    break;
                }
                on(i, pr[j]);
            }
        }
    }
    //线性筛: pr[] 所有素数
    static void get_prime(const int n, bool not_pri[], int pr[], int &cnt) {
        sieve_mul_func(n, not_pri, pr, cnt, [&](const int i) {}, [&](const int i, const int pr_) {}, [&](const int i, const int pr_) {});
    }
    //线性求欧拉函数: phi[] 欧拉函数, pr[] 所有素数
    static void get_phi(const int n, bool not_pri[], int pr[], int &cnt, int phi[]) {
        phi[1] = 1;
        sieve_mul_func(n, not_pri, pr, cnt, [&](const int i) { phi[i] = i - 1; },
                       [&](const int i, const int pr_) { phi[i * pr_] = pr_ * phi[i]; },
                       [&](const int i, const int pr_) { phi[i * pr_] = phi[i] * (pr_ - 1); });
    }
    //线性求因子个数: d[] 因子个数, expo[] 最小质因子的幂指数, pr[] 所有素数
    static void get_fac_cnt(const int n, bool not_pri[], int pr[], int &cnt, int d[], int expo[]) {
        sieve_mul_func(n, not_pri, pr, cnt, [&](const int i) { d[i] = 2, expo[i] = 1; },
                       [&](const int i, const int pr_) {
                           d[i * pr_] = d[i] / (expo[i] + 1) * (expo[i] + 2), expo[i * pr_] = expo[i] + 1;
                       },
                       [&](const int i, const int pr_) {
                           d[i * pr_] = d[i] * d[pr_], expo[i * pr_] = 1;
                       });
    }
    //线性求莫比乌斯函数 μ: mu[] μ函数, pr[] 所有素数
    static void get_mu(const int n, bool not_pri[], int pr[], int &cnt, int mu[]) {
        sieve_mul_func(n, not_pri, pr, cnt, [&](const int i) { mu[i] = 1; },
                       [&](const int i, const int pr_) { mu[i * pr_] = 0; },
                       [&](const int i, const int pr_) { mu[i * pr_] = -mu[i]; });
    }
//------其他------
    static int inv_ex(const int n, const int m = mod) {
        int x, y;
        if (exgcd(n, m, x, y) == 1) return (x % m + m) % m;
        return -1;
    }
    //ax+by=gcd(a,b),返回gcd
    static int exgcd(const int a, const int b, int &x, int &y) {
        if (!b) {
            x = 1, y = 0;
            return a;
        }
        const int d = exgcd(b, a % b, x, y), t = x;
        x = y; y = t - a / b * y;
        return d;
    }
    //x (mod M_i) = A_i
    static int exCRT(const int n, const int M_[], int A_[]) {
        int a = A_[1], m = M_[1], ta, tm, x, y;
        for (int i = 2; i <= n; i ++) {
            tm = M_[i], ta = A_[i];
            const int d = exgcd(m, tm, x, y), l = m * tm / d;
            if ((ta - a) % d != 0) return -1;
            const int t = tm / d;
            x = (x * ((ta - a) / d % t) % t + t) % t;
            a += m * x;
            m = l;
        }
        return a;
    }
    static int C(int m, int n, const int p = mod) {
        int a = 1, b = 1;
        if (m < n) return 0;
        while (n) a = a * (m --) % p, b = b * (n --) % p;
        return a * inv_ex(b, p) % p;
    }
    //p为1e5以内质数，求C(n, m) % p
    static int lucas(const int n, const int m, const int p = mod) {
        if (m == 0) return 1;
        return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
    }
private:  //Adapted from LH_Frank's Code Template
    struct PRIME {
        int check_num = 0, max_factor = 0;
        vector<pair<int, int>> dec;
    private:
        void get_fac(int x) { //寻找 x 的最大因子
            if (x <= max_factor || x < 2) return;
            if (miller_rabin(x)) return void(max_factor = max(max_factor, x));
            int fac = x;
            while (fac >= x) fac = pollard_rho(x); //寻找因子
            while (!(x % fac)) x /= fac;
            return get_fac(x), get_fac(fac);
        }
        void decomposition(int x) { // 分解 x 的质因子
            if (x < 2) return;
            if (miller_rabin(x)) {
                pair<int, int> now = {x, 0};
                while (check_num % x == 0) now.second++, check_num /= x;
                if (now.second) dec.emplace_back(now);
                return;
            }
            int fac = x;
            while (fac >= x) fac = pollard_rho(x); //寻找因子
            while (!(x % fac)) x /= fac;
            return decomposition(x), decomposition(fac);
        }
    public:
        static bool miller_rabin(const __int128 p){ //检测 p 是不是质数, 严格保证答案正确
            const __int128 test[16] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 61, 325, 9375, 28178, 450775, 9780504, 1795265022};
            if (p < 3 || p % 2 == 0) return p == 2;
            static int i, j;
            static __int128 tmp, k, next;
            tmp = p - 1, k = 0;
            while (tmp % 2 == 0) tmp >>= 1, ++k;
            for (j = 1; j <= 15; j++) {
                next = qp(test[j], tmp, p);
                if (next <= 1 || next == p - 1) continue;
                for (i = 0; i < k; ++i) {
                    next = next * next % p;
                    if (next == p - 1 && i != k - 1) {
                        next = 1;
                        break;
                    }
                    if (next == 1) return false;
                }
                if (next != 1) return false;
            }
            return true;
        }
        static bool r_miller_rabin(const __int128 p, const int test_time = 8) { //检测 p 是不是质数, 基于随机检验
            if (p < 3 || p % 2 == 0) return p == 2;
            static int i, j;
            static __int128 tmp, k, rand_num, now;
            tmp = p - 1, k = 0;
            while (tmp % 2 == 0) tmp >>= 1, ++k;
            for (i = 1; i <= test_time; ++i) {
                rand_num = rand() % (p - 2) + 2, now = qp(rand_num, tmp, p);
                if (now == 1) continue;
                for (j = 0; j < k; ++j) {
                    if (now == p - 1) break;
                    now = now * now % p;
                }
                if (j >= k) return false;
            }
            return true;
        }
        static int pollard_rho(int x) {
            static int s, t, c, div, val;
            val = 1, s = t = 0;
            static int step, goal;
            step = 0, goal = 1;
            c = (int) rand() % (x - 1) + 1;
            for (goal = 1;; goal <<= 1, s = t, val = 1) { //倍增优化
                for (step = 1; step <= goal; ++step) {
                    t = ((__int128) t * t + c) % x, val = (__int128) val * abs(t - s) % x;
                    if (!(step % 127)) {
                        div = __gcd(val, x);
                        if (div > 1) return div;
                    }
                }
                div = __gcd(val, x);
                if (div > 1) return div;
            }
        }
        void get_max_fac(const int x) { return max_factor = 0, get_fac(x); } //获得 x 的最大因子  测 试: Luogu P4718
        void dec_factor(const int x) { return dec.clear(), check_num = x, decomposition(x); } //分解 x 的本质不同质因子  测 试: Prime Land
        int get_phi(int x) { //计算 φ(x)
            if (x == 1) return 0;
            dec_factor(x);
            for (const auto &[fst, snd]: dec) x = x / fst * (fst - 1);
            return x;
        }
    } pm;
public:
    //欧拉函数，小于等于n和n互质的数的个数
    int phi(const int n) { return pm.get_phi(n); }
    vector<pair<int, int>> factorize(const int x) { return pm.dec_factor(x), pm.dec; }
    int max_factor(const int x){ return pm.get_max_fac(x), pm.max_factor; }
    bool miller_rabin(const __int128 P) const { return pm.miller_rabin(P); }
    void random_miller_rabin(const __int128 P, const int test_time = 8) const { pm.r_miller_rabin(P, test_time); }
    int pollard_pho(const int x) const { return pm.pollard_rho(x); }
} math;