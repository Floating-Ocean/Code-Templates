#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

//后缀数组，n log n，倍增+计数排序+常数优化
struct SuffixArray {
    int n;
    vector<int> sa, rk, lc;  //sa[i]: 排名第i的开始下标, rk[i]: 开始下标i的排名, lc[i] = lcp(sa[i],sa[i+1])

    explicit SuffixArray(string &s) {
        n = s.size();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        iota(sa.begin(), sa.end(), 0ll);
        sort(sa.begin(), sa.end(), [&](int a, int b){
            return s[a] < s[b];
        });
        rk[sa[0]] = 0;
        for(int i=1;i<n;i++) {
            rk[sa[i]] = rk[sa[i - 1]];
            if(s[sa[i]] != s[sa[i - 1]]) rk[sa[i]] ++;
        }
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while(rk[sa.back()] < n - 1) {
            tmp.clear(); //tmp: id
            for(int i=0;i<k;i++) tmp.emplace_back(n - k + i);
            for(auto &it : sa) {
                if(it < k) continue;
                tmp.emplace_back(it - k);
            }
            fill(cnt.begin(), cnt.end(), 0ll);
            for(int i=0;i<n;i++) cnt[rk[i]] ++;
            for(int i=1;i<n;i++) cnt[i] += cnt[i - 1];
            for(int i=n-1;i>=0;i--) sa[--cnt[rk[tmp[i]]]] = tmp[i];
            swap(rk, tmp); //tmp: old_rk
            rk[sa[0]] = 0;
            for(int i=1;i<n;i++) {
                rk[sa[i]] = rk[sa[i - 1]];
                if(tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]) rk[sa[i]] ++;
            }
            k <<= 1ll;
        }
        for (int i=0,j=0;i<n;i++) {
            if (rk[i] == 0) j = 0;
            else {
                for (j-=j>0;i+j<n && sa[rk[i]-1]+j<n && s[i+j]==s[sa[rk[i]-1]+j];) j ++;
                lc[rk[i] - 1] = j;
            }
        }
    }
};
