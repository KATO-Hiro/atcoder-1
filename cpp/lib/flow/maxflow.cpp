#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VI = vector<int>;
// --------------------------------------------------------
#include <atcoder/maxflow>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N, M, E; cin >> N >> M >> E;
    VI P(M); REP(i,M) cin >> P[i];

    mf_graph<ll> G(N + 1);
    int s = 0, t = N;
    int a, b;
    REP(_,E) {
        cin >> a >> b;
        G.add_edge(a, b, 1);
        G.add_edge(b, a, 1);
    }
    for (int p : P) {
        G.add_edge(p, t, 1);
    }

    int ans = G.flow(s, t);
    cout << ans << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/abc010/tasks/abc010_4
