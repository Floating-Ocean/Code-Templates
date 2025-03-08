#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

void solve() {
    string s;
    while(getline(cin, s)){
        while(!s.empty() && s[0] >= '0' && s[0] <= '9') s.erase(s.begin());
        cout << regex_replace(regex_replace(s, regex("␣"), " "), regex("−"), "-") << '\n';
    }
}

signed main() {
# ifdef FLOATING_OCEAN
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
# endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
//    cin >> t;
    while (t--) solve();
}