#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct PAM {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len, link, cnt; //cnt[i]: 以i结尾的回文串个数
        array<int, ALPHABET> next;
        Node(): len{}, link{}, cnt{}, next{} {}
    };
    vector<Node> t;
    int suff;
    string s;

    explicit PAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].len = -1;
        suff = 1;
        s.clear();
    }
    int new_node() {
        t.emplace_back();
        return t.size() - 1;
    }
    bool add(const char &c) { //返回是否有新节点添加
        int pos = s.size();
        s += c;
        int let = c - 'a';
        int cur = suff, cur_len;
        while(true) {  //跳fail指针，直到两端字符匹配，找到回文
            cur_len = t[cur].len;
            if(pos - cur_len - 1 >= 0 && s[pos - cur_len - 1] == s[pos]) {
                break;
            }
            cur = t[cur].link; //最长回文后缀
        }
        if(t[cur].next[let]) {
            suff = t[cur].next[let];
            return false;
        }
        int num = new_node();
        suff = num;
        t[num].len = t[cur].len + 2;
        t[cur].next[let] = num;
        if(t[num].len == 1) {
            t[num].link = 1;
            t[num].cnt = 1;
            return true;
        }
        while(true) { //更新fail
            cur = t[cur].link;
            cur_len = t[cur].len;
            if(pos - cur_len - 1 >= 0 && s[pos - cur_len - 1] == s[pos]) {
                t[num].link = t[cur].next[let];
                break;
            }
        }
        t[num].cnt = t[t[num].link].cnt + 1;
        return true;
    }
    int next(int p, int x) const {
        return t[p].next[x];
    }
    int link(int p) const {
        return t[p].link;
    }
    int len(int p) const {
        return t[p].len;
    }
    int size() const {
        return t.size();
    }
};

void solve() {  //求所有回文子串中的 max(长度平方*出现次数）
    string s;
    cin >> s;
    int n = s.size();
    PAM pam;
    vector<int> suf(n);
    for(int i=0;i<n;i++) {
        pam.add(s[i]);
        suf[i] = pam.suff;
    }
    vector<int> dp(pam.size());
    for(int i=0;i<n;i++) {
        dp[suf[i]] ++;
    }
    vector<vector<int>> adj(pam.size());
    for(int i=2;i<pam.size();i++) {
        adj[pam.link(i)].emplace_back(i);
    }
    int ans = 0;
    auto dfs = [&](auto self, int x) -> void {
        for(auto &y : adj[x]) {
            self(self, y);
            dp[x] += dp[y];
        }
        ans = max(ans, pam.len(x) * pam.len(x) * dp[x]);
    };
    dfs(dfs, 1);
    cout << ans << '\n';
}