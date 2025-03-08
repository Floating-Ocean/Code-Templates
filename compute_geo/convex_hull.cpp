#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int N = 2e5 + 10, M = 2e5 + 10, mod = 998244353, inf = 0x3f3f3f3f3f3f3f3f;

struct Point {
    double x, y, ang;

    Point operator-(const Point& p) const { return {x - p.x, y - p.y, 0}; }
} p[N], q[N];

double dis(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool cmp(Point p1, Point p2) {
    if (p1.ang == p2.ang) {
        return dis(p1, p[1]) < dis(p2, p[1]);
    }
    return p1.ang < p2.ang;
}

double cross(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }

bool isPointOnRight(const Point& A, const Point& B, const Point& P) {
    double cross_product = cross(P - A, B - A);
    if (cross_product > 0) {
        return true;  // 点P在直线AB的右侧
    } else if (cross_product < 0) {
        return false;  // 点P在直线AB的左侧
    } else {
        return false;  // 点P在直线AB上
    }
}

void solve(){
    int m;
    cin >> m;
    for(int i=0;i<=m;i++){
        int x;
        cin >> x;
        q[i + 1].x = x, q[i + 1].y = i;
    }
    int n = 1;
    p[1] = q[1];
    for(int i=2;i<=m;i++){
        if(isPointOnRight(q[1], q[m + 1], q[i])) p[++ n] = q[i];
    }
    p[++ n] = q[m + 1];
    double ans = -sqrt((p[1].x - p[n].x) * (p[1].x - p[n].x) + (p[1].y - p[n].y) * (p[1].y - p[n].y));
    for (int i = 2; i <= n; ++i) {
        if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x)) {
            swap(p[1], p[i]);
        }
    }
    for (int i = 2; i <= n; ++i) {
        p[i].ang = atan2(p[i].y - p[1].y, p[i].x - p[1].x);
    }
    sort(p + 2, p + n + 1, cmp);
    vector<int> sta(n + 10);
    int top = 0;
    sta[++top] = 1;
    for (int i = 2; i <= n; ++i) {
        while (top >= 2 &&
               cross(p[sta[top]] - p[sta[top - 1]], p[i] - p[sta[top]]) < 0) {
            top--;
        }
        sta[++top] = i;
    }
    for(int i=1;i<top;i++) {
        ans += sqrtl((p[sta[i]].x - p[sta[i + 1]].x) * (p[sta[i]].x - p[sta[i + 1]].x) + (p[sta[i]].y - p[sta[i + 1]].y) * (p[sta[i]].y - p[sta[i + 1]].y));
    }
    ans += sqrtl((p[sta[1]].x - p[sta[top]].x) * (p[sta[1]].x - p[sta[top]].x) + (p[sta[1]].y - p[sta[top]].y) * (p[sta[1]].y - p[sta[top]].y));
    cout << fixed << setprecision(10) << ans << '\n';
}