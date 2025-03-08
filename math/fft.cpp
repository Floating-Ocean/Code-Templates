#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct FFT {
    using cd = complex<double>;
    void f(vector<cd> &a, bool invert) {
        int n = a.size();
        if (n == 1) return;
        vector<cd> a0(n / 2), a1(n / 2);
        for (int i = 0; 2 * i < n; i++) a0[i] = a[2 * i], a1[i] = a[2 * i + 1];
        f(a0, invert), f(a1, invert);
        double ang = 2 * acos(-1.0) / n * (invert ? -1 : 1);
        cd w(1), wn(cos(ang), sin(ang));
        for (int i = 0; 2 * i < n; i++) {
            a[i] = a0[i] + w * a1[i], a[i + n/2] = a0[i] - w * a1[i];
            if (invert) a[i] /= 2, a[i + n/2] /= 2;
            w *= wn;
        }
    }
} fft;