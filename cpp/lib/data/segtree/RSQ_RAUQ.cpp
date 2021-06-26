#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間加算+更新・区間総和
struct S { ll v; ll num; };
struct F { ll x; ll q; };  // q = 1 (add), 2 (update)
S op(S a, S b) { return S{a.v + b.v, a.num + b.num}; }
S e() { return S{0, 0}; }
S mapping(F f, S a) {
    if (f.q == 1) { return S{a.v + f.x * a.num, a.num}; }
    if (f.q == 2) { return S{f.x * a.num, a.num}; }
    assert(false);
}
F composition(F f, F g) {
    if (f.q == 1 && g.q == 1) { return F{f.x + g.x, 1}; }
    if (f.q == 1 && g.q == 2) { return F{f.x + g.x, 2}; }
    if (f.q == 2) { return F{f.x , 2}; }
    assert(false);
}
F id() { return F{0, 1}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    VLL t(N); REP(i,N) cin >> t[i];
    vector<S> X(N); REP(i,N) X[i] = S{t[i], 1};
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(X);

    while (Q--) {
        ll q; cin >> q;
        if (q == 1 || q == 2) {
            ll l, r, x; cin >> l >> r >> x;
            l--; r--;
            seg.apply(l, r+1, F{x, q});
        } else {
            ll l, r; cin >> l >> r;
            l--; r--;
            cout << seg.prod(l, r+1).v << '\n';
        }
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1735
