#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

signed main() {
    long long cnt = 0;
    while (true) {
        system("random.exe > test1.in");
        system("std.exe < test1.in > test1.std.out");
        system("usr.exe < test1.in > test1.usr.out");
        if (system("fc test1.std.out test1.usr.out")) {
            cerr << "Test" << ++cnt << ": WA\n";
            break;
        }
        cerr << "Test" << ++cnt << ": OK\n";
    }
}