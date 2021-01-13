#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
using VLL = vector<ll>;
// --------------------------------------------------------

struct Point {
    ll x, y;
    ll id;
    bool operator<(const Point& p) const { return id < p.id; }
};

bool lessX(Point& p1, Point& p2) { return p1.x < p2.x; }
bool lessY(Point& p1, Point& p2) { return p1.y < p2.y; }

struct kdtree {
    struct Node { ll l, r, loc; };
    vector<Point> P;
    vector<Node> T;
    ll np = 0;
    kdtree(const ll N) { init(N); }

    void init(const ll N) {
        P = vector<Point>(N);
        T = vector<Node>(N);
    }

    ll make(ll l, ll r, ll d) {
        if (!(l < r)) return -1;
        ll mid = (l + r) / 2;
        ll t = np++;
        sort(P.begin() + l, P.begin() + r, (d ? lessX : lessY));
        T[t].loc = mid;
        T[t].l = make(l, mid, !d);
        T[t].r = make(mid+1, r, !d);
        return t;
    }

    void find(ll v, ll x1, ll x2, ll y1, ll y2, ll d, vector<Point>& S) {
        ll x = P[T[v].loc].x;
        ll y = P[T[v].loc].y;
        if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
            S.push_back(P[T[v].loc]);
        }
        if (d) {
            if (T[v].l != -1 && x1 <= x) find(T[v].l, x1, x2, y1, y2, !d, S);
            if (T[v].r != -1 && x <= x2) find(T[v].r, x1, x2, y1, y2, !d, S);
        } else {
            if (T[v].l != -1 && y1 <= y) find(T[v].l, x1, x2, y1, y2, !d, S);
            if (T[v].r != -1 && y <= y2) find(T[v].r, x1, x2, y1, y2, !d, S);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    kdtree kd(N);
    ll x, y;
    REP(i,N) {
        cin >> x >> y;
        kd.P[i] = Point{x, y, i};
    }

    ll root = kd.make(0, N, 0);

    ll Q; cin >> Q;
    ll x1, x2, y1, y2;
    vector<Point> S;
    while (Q--) {
        cin >> x1 >> x2 >> y1 >> y2;
        S.clear();
        kd.find(root, x1, x2, y1, y2, 0, S);
        SORT(S);
        for (auto& p : S) {
            cout << p.id << '\n';
        }
        cout << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_C&lang=ja
