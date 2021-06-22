#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/maxflow>
using namespace atcoder;

// References:
//   <https://en.wikipedia.org/wiki/Cut_(graph_theory)>


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;

    ll s = 0, t = N - 1;
    mf_graph<ll> G(N);
    REP(_,M) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G.add_edge(u, v, 1);
        G.add_edge(v, u, 1);
    }

    cout << G.flow(s, t) << endl;

    // 最小カット (S,T)
    // true : S 側  false : T 側
    vector<bool> mc = G.min_cut(s);

    // 最小カットを横切る辺の列挙 (cut-set)
    for (auto e : G.edges()) {
        if (mc[e.from] && !mc[e.to]) {
            int u = e.from + 1;
            int v = e.to + 1;
            cout << u << " " << v << '\n';
        }
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1695
