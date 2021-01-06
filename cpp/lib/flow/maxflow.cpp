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

    ll N, M; cin >> N >> M;
    ll s = 0, t = N - 1;
    mf_graph<ll> G(N + 1);
    ll u, v, c;
    REP(_,M) {
        cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }

    ll ans = G.flow(s, t);
    cout << ans << endl;;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja
