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

struct BIGINT {
    using cd = complex<double>;
    void multiplyAndPrint(string num1, string num2) {
        int sz1 = num1.size(), sz2 = num2.size();
        vector<cd> fa(sz1), fb(sz2);
        for (int i = 0; i < sz1; i++) fa[i] = num1[sz1 - 1 - i] - '0';
        for (int i = 0; i < sz2; i++) fb[i] = num2[sz2 - 1 - i] - '0';
        int n = 1;
        while (n < sz1 + sz2) n <<= 1ll;
        fa.resize(n), fb.resize(n);
        fft.f(fa, false), fft.f(fb, false);
        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        fft.f(fa, true);
        vector<int> result(n);
        int carry = 0;
        for (int i = 0; i < n; i++) {
            result[i] = round(fa[i].real()) + carry;
            carry = result[i] / 10;
            result[i] %= 10;
        }
        while (n > 1 && result[n - 1] == 0) n --;
        for (int i = n - 1; i >= 0; i--) cout << result[i];
    }
} bigint;