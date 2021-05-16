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
pair<VLL, VLL> euler_tour(const VVLL& G, ll root = 0) {
    const ll N = SZ(G);
    VLL L(N), R(N);
    ll idx = 0;
    auto dfs = [&](auto self, ll u, ll p) -> void {
        L[u] = idx++;
        for (ll v : G[u]) if (v != p) {
            self(self, v, u);
        }
        R[u] = idx++;
    };
    dfs(dfs, root, -1);
    return make_pair(L, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL G(N);
    REP(u,N) {
        ll k; cin >> k;
        while (k--) {
            ll c; cin >> c;
            G[u].push_back(c);
            G[c].push_back(u);
        }
    }

    auto [L, R] = euler_tour(G, 0);
    segtree<S, op, e> seg(2*N);  // Euler Tour により 2N 必要

    ll Q; cin >> Q;
    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll v, w; cin >> v >> w;
            seg.set(L[v], seg.get(L[v]) + w);
            seg.set(R[v], seg.get(R[v]) - w);
        } else {
            ll u; cin >> u;
            ll ans = seg.prod(0, L[u] + 1);
            cout << ans << '\n';
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D&lang=ja
