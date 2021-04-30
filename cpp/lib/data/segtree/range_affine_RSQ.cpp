#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/modint>
#include <atcoder/lazysegtree>
using namespace atcoder;

using mint = modint998244353;

// 区間アフィン変換・区間総和
struct S { mint a; ll n; };
struct F { mint b, c; };
S op(S x, S y) { return S{x.a + y.a, x.n + y.n}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return S{f.b * x.a + f.c * x.n, x.n}; }
F composition(F f, F g) { return F{f.b * g.b, g.c * f.b + f.c}; }
F id() { return F{1, 0}; }


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    vector<S> A(N);
    REP(i, N) {
        ll a; cin >> a;
        A[i] = S{a, 1};
    }
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    while (Q--) {
        ll q, l, r; cin >> q >> l >> r;
        if (q == 0) {
            ll b, c; cin >> b >> c;
            seg.apply(l, r, F{b, c});
        } else {
            cout << seg.prod(l, r).a.val() << '\n';
        }
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/practice2/tasks/practice2_k
