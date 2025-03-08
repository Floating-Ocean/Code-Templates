#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0ll, min(l + z[l] - i, z[i - l]));
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i] ++;
        if(i + z[i] > l + z[l]) l = i;
    }
    return z;
}