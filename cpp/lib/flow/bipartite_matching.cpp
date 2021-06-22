#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/maxflow>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M, K; cin >> N >> M >> K;
    ll s = N + M, t = s + 1;
    mf_graph<ll> G(N + M + 2);
    REP(i,N) G.add_edge(s, i, 1);
    REP(i,M) G.add_edge(N+i, t, 1);
    REP(_,K) {
        ll a, b; cin >> a >> b;
        a--; b--;
        G.add_edge(a, N+b, 1);
    }

    cout << G.flow(s, t) << endl;

    // ペアの復元
    for (auto e : G.edges()) {
        if (e.from == s || e.to == t || e.flow == 0) continue;
        int u = e.from + 1;
        int v = e.to - N + 1;
        cout << u << " " << v << '\n';
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1696


/**
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll X, Y, E; cin >> X >> Y >> E;
    ll s = X + Y, t = s + 1;
    mf_graph<ll> G(X + Y + 2);
    REP(x, X) G.add_edge(s, x, 1);
    REP(y, Y) G.add_edge(X + y, t, 1);
    REP(_, E) {
        ll x, y; cin >> x >> y;
        G.add_edge(x, X + y, 1);
    }
    cout << G.flow(s, t) << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A&lang=ja
**/
