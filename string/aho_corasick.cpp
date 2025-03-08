#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len, link;
        array<int, ALPHABET> next;
        vector<int> idx;
        Node(): len{}, link{}, next{} {}
    };
    vector<Node> t;

    explicit AhoCorasick() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int new_node() {
        t.emplace_back();
        return t.size() - 1;
    }
    int add(const string &a, int idx) {
        int p = 1;
        for(auto &c : a) {
            int x = c - 'a';
            if(t[p].next[x] == 0) {
                t[p].next[x] = new_node();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        t[p].idx.emplace_back(idx);
        return p;
    }
    void work() {
        queue<int> q;
        q.emplace(1);
        while(!q.empty()) {
            int x = q.front();
            q.pop();
            for(int i=0;i<ALPHABET;i++) {
                if(t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];  //失配后直接跳转的结点
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.emplace(t[x].next[i]);
                }
            }
        }
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
    //查询n个模式串在a中的出现次数，模式串可重复
    vector<int> query(const string &a, int n) & {
        vector<int> cnt(n + 1), val(t.size());
        int p = 1;
        for(auto &c : a) {
            int x = c - 'a';
            p = t[p].next[x];
            for(int q=p;q>1;q=t[q].link) val[q] ++;
        }
        for(int i=1;i<t.size();i++) {
            for(auto &it : t[i].idx) cnt[it] = val[i];
        }
        return cnt;
    }
};