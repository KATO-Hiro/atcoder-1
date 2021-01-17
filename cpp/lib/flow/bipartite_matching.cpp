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
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll X, Y, E; cin >> X >> Y >> E;
    mf_graph<ll> G(X + Y + 2);
    ll s = X + Y, t = s + 1;
    REP(x, X) G.add_edge(s, x, 1);
    REP(y, Y) G.add_edge(y + X, t, 1);
    REP(_, E) {
        ll x, y; cin >> x >> y;
        G.add_edge(x, y + X, 1);
    }
    cout << G.flow(s, t) << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A&lang=ja
