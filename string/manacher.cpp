#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

//马拉车算法 计算以任意点为中心的回文串的最大长度
struct MLC {
    vector<int> manacher(string target) {
        string s;
        int len = ((int) target.size() << 1) + 3;
        s.resize(len);
        s[0] = '$', s[1] = '#', s[len - 1] = 0;
        for (int i = 0; i < target.size(); i++) s[(i + 1) << 1] = target[i], s[((i + 1) << 1) + 1] = '#';
        vector<int> ans(len);
        int mx = 0, id = 0; //mx是右端点max
        for (int i = 0; i < len; i++) {
            ans[i] = mx > i ? min(ans[(id << 1) - i], mx - i) : 1;
            while (s[i + ans[i]] == s[i - ans[i]]) ans[i]++; //中心拓展
            if (i + ans[i] > mx) mx = i + ans[i], id = i; //方便判之后会不会被包在这个区间里
        }
        return ans;
    }
} mlc;
