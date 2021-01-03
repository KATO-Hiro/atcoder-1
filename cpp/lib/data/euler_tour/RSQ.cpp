#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点加算・区間総和
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }

// オイラーツアー
//   - L[u]: 頂点 u がオイラーツアー上で最初に現れるインデックス
//   - R[u]: 頂点 u がオイラーツアー上で最後に現れるインデックスの次
pair<VLL, VLL> euler_tour(VVLL& G, ll root = 0) {
    const ll N = SZ(G);
    VLL L(N), R(N);
    ll idx = 0;
    auto dfs = [&](auto f, ll u, ll p) -> void {
        L[u] = idx++;
        for (ll v : G[u]) {
            if (v == p) continue;
            f(f, v, u);
        }
        R[u] = idx++;
    };
    dfs(dfs, root, -1);
    return make_pair(L, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N; cin >> N;
    VVLL G(N);
    ll k, c;
    REP(u,N) {
        cin >> k;
        while (k--) {
            cin >> c;
            G[u].push_back(c);
            G[c].push_back(u);
        }
    }

    VLL L, R;
    tie(L, R) = euler_tour(G, 0);
    segtree<S, op, e> seg(2*N);  // Euler Tour により 2N 必要

    ll Q; cin >> Q;
    ll q, u, v, w;
    while (Q--) {
        cin >> q;
        if (q == 0) {
            cin >> v >> w;
            seg.set(L[v], seg.get(L[v]) + w);
            seg.set(R[v], seg.get(R[v]) - w);
        } else {
            cin >> u;
            ll ans = seg.prod(0, L[u] + 1);
            cout << ans << '\n';
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D&lang=ja
