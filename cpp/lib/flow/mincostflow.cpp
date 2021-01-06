#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/mincostflow>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M, F; cin >> N >> M >> F;
    ll s = 0, t = N - 1;
    mcf_graph<ll,ll> G(N);
    ll u, v, c, d;
    REP(_,M) {
        cin >> u >> v >> c >> d;
        G.add_edge(u, v, c, d);
    }

    auto result = G.flow(s, t, F);
    ll ans = (result.first < F) ? -1 : result.second;
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B&lang=ja
