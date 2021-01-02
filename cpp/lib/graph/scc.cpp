#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
// --------------------------------------------------------
#include <atcoder/scc>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;

    scc_graph G(N);
    ll a, b;
    REP(_,M) {
        cin >> a >> b;
        G.add_edge(a, b);
    }

    auto scc = G.scc();
    cout << SZ(scc) << '\n';
    for (auto& g : scc) {
        cout << SZ(g);
        for (auto& u : g) {
            cout << " " << u;
        }
        cout << '\n';
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/practice2/tasks/practice2_g
