#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点加算・区間総和
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }


#include "hld.cpp"


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    VLL A(N); REP(i,N) cin >> A[i];
    HLD hld(N,0);
    REP(_,N-1) {
        ll u, v; cin >> u >> v;
        // u--; v--;
        hld.add_edge(u, v);
    }
    hld.build();
    bool edge = false;

    vector<S> X(N);
    REP(u,N) X[hld.in[u]] = A[u];
    segtree<S, op, e> seg(X);

    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll u, x; cin >> u >> x;
            // u--;
            hld.apply_path(u, u, edge, [&](int l, [[maybe_unused]] int r) {
                seg.set(l, seg.get(l) + x);
            });
        } else {
            ll u, v; cin >> u >> v;
            // u--; v--;
            ll ans = hld.prod_path<S,op,e>(u, v, edge, [&](int l, int r) {
                return seg.prod(l, r+1);
            });
            cout << ans << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.yosupo.jp/problem/vertex_add_path_sum
