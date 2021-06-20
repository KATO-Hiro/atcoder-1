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

    ll N; cin >> N;
    HLD hld(N,0);
    REP(u,N) {
        ll k; cin >> k;
        while (k--) {
            ll c; cin >> c;
            hld.add_edge(u, c);
        }
    }
    hld.build();
    bool edge = true;

    vector<S> X(N, S{0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(X);

    ll Q; cin >> Q;
    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll v, w; cin >> v >> w;
            // v--;
            hld.apply_path(0, v, edge, [&](int l, int r) {
                seg.apply(l, r+1, F{w});
            });
        } else {
            ll u; cin >> u;
            // u--;
            S res = hld.prod_path<S,op,e>(0, u, edge, [&](int l, int r) {
                return seg.prod(l, r+1);
            });
            cout << res.v << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E&lang=ja
