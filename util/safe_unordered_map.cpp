#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

//Codeforces 防叉 unordered_map
namespace safe_unordered_map {
    struct custom_hash {
        static uint64_t splitMix64(uint64_t x) {
            x ^= x << 13;
            x ^= x >> 7;
            x ^= x << 17;
            return x;
        }
        size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
            return splitMix64(x + FIXED_RANDOM);
        }
    };
    template<typename Val = int>
    using un_map = unordered_map<uint64_t, Val, custom_hash>;
} using namespace safe_unordered_map;