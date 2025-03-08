#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct KMP {
    //kmp前缀和函数
    vector<int> prefix_function(string s) {
        int n = (int) s.length();
        vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }

    //pattern在text中出现的下标
    vector<pair<int, int>> find_occur(const string &text, const string &pattern, bool noOverlap = false) {
        string cur = pattern + '#' + text;
        int sz1 = (int) text.size(), sz2 = (int) pattern.size();
        vector<pair<int, int>> v;
        vector<int> lps = prefix_function(cur);
        for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
            if (lps[i] == sz2) {
                if (noOverlap && !v.empty() && i - 2 * sz2 < v.back().second + 1) continue;
                v.emplace_back(i - 2 * sz2, i - sz2 - 1);
            }
        }
        return v;
    }
}kmp;