#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/scc>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    scc_graph G(N);
    ll s, t;
    REP(_,M) {
        cin >> s >> t;
        G.add_edge(s, t);
    }

    auto scc = G.scc();
    VLL scc_id(N);  // 各頂点の強連結成分の番号
    REP(i,SZ(scc)) {
        for (auto& u : scc[i]) {
            scc_id[u] = i;
        }
    }

    ll Q; cin >> Q;
    ll u, v;
    while (Q--) {
        cin >> u >> v;
        cout << (scc_id[u] == scc_id[v] ? 1 : 0) << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=ja

/*
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
*/
