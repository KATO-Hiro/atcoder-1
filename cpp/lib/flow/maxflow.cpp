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

    // ll s = N, t = s + 1;
    // mf_graph<ll> G(N+2);
    ll s = 0, t = N - 1;
    mf_graph<ll> G(N);
    REP(_,M) {
        ll u, v, c; cin >> u >> v >> c;
        // u--; v--;
        G.add_edge(u, v, c);
    }

    ll ans = G.flow(s, t);
    cout << ans << endl;

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja
