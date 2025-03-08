#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<uint64_t mod1 = 4294967291ULL, uint64_t mod2 = 4294967279ULL>
struct DoubleHash {
    size_t n;
    vector<uint64_t> p, q, hs1, hs2;
    explicit DoubleHash(const string &s): n(s.size()), p(n + 1), q(n + 1), hs1(n + 1), hs2(n + 1) {
        static const uint64_t FIXED_RANDOM = std::chrono::system_clock::now().time_since_epoch().count();
        static mt19937_64 engine(FIXED_RANDOM);
        static uniform_int_distribution<uint64_t> rnd1(1001, 1499), rnd2(1501, 1999);
        static const uint64_t P = rnd1(engine), Q = rnd2(engine);
        p[0] = q[0] = 1;
        for(int i=1;i<=n;i++) {
            p[i] = p[i - 1] * P % mod1, q[i] = q[i - 1] * Q % mod2;
            hs1[i] = (hs1[i - 1] * P % mod1 + s[i - 1]) % mod1, hs2[i] = (hs2[i - 1] * Q % mod2 + s[i - 1]) % mod2;
        }
    }
    pair<uint64_t, uint64_t> operator()(const int l, const int r) const {
        return {(hs1[r] + mod1 - hs1[l - 1] * p[r - l + 1] % mod1) % mod1, (hs2[r] + mod2 - hs2[l - 1] * q[r - l + 1] % mod2) % mod2};
    }
};

template<uint64_t mod1 = 4294967291ULL>
struct SingleHash {
    size_t n;
    vector<uint64_t> p, hs1;
    explicit SingleHash(const string &s): n(s.size()), p(n + 1), hs1(n + 1){
        static const uint64_t FIXED_RANDOM = std::chrono::system_clock::now().time_since_epoch().count();
        static mt19937_64 engine(FIXED_RANDOM);
        static uniform_int_distribution<uint64_t> rnd1(1001, 1999);
        static const uint64_t P = rnd1(engine);
        p[0] = 1;
        for(int i=1;i<=n;i++) {
            p[i] = p[i - 1] * P % mod1;
            hs1[i] = (hs1[i - 1] * P % mod1 + s[i - 1]) % mod1;
        }
    }
    uint64_t operator()(const int l, const int r) const {
        return (hs1[r] + mod1 - hs1[l - 1] * p[r - l + 1] % mod1) % mod1;
    }
};

