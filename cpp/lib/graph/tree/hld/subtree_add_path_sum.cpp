#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間加算・区間総和
struct S { ll v; ll num; };
struct F { ll x; };
S op(S a, S b) { return S{a.v + b.v, a.num + b.num}; }
S e() { return S{0, 0}; }
S mapping(F f, S a) { return S{a.v + f.x * a.num, a.num}; }
F composition(F f, F g) { return F{f.x + g.x}; }
F id() { return F{0}; }


#include "hld.cpp"


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    HLD hld(N,0);
    REP(_,N-1) {
        ll u, v; cin >> u >> v;
        // u--; v--;
        hld.add_edge(u, v);
    }
    hld.build();
    bool edge = true;

    vector<S> X(N, S{0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(X);

    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll u, v; cin >> u >> v;
            // u--; v--;
            S res = hld.prod_path<S,op,e>(u, v, edge, [&](int l, int r) {
                return seg.prod(l, r+1);
            });
            cout << res.v << '\n';
        } else {
            ll u, x; cin >> u >> x;
            // u--;
            hld.apply_subtree(u, edge, [&](int l, int r) {
                seg.apply(l, r+1, F{x});
            });
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667
