#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;
constexpr double eps = 1e-9;

struct Ternary_Search {
    double lts(double l, double r, auto f) {
        double mid, midl;
        while (fabs(r - l) > eps) {
            mid = (l + r) / 2;
            midl = (mid + l) / 2;
            if (f(mid) > f(midl)) r = mid; else l = midl;
        }
        return f(l);
    }
    double rts(double l, double r, auto f) {
        double mid, midr;
        while (fabs(r - l) > eps) {
            mid = (l + r) / 2;
            midr = (mid + r) / 2;
            if (f(mid) < f(midr)) l = mid; else r = midr;
        }
        return f(l);
    }
} ts;