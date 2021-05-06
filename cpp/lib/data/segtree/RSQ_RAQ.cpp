#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, Q; cin >> N >> Q;
    vector<S> A(N, S{0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll s, t, x; cin >> s >> t >> x;
            s--; t--;
            seg.apply(s, t + 1, F{x});
        } else {
            ll s, t; cin >> s >> t;
            s--; t--;
            cout << seg.prod(s, t + 1).v << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G&lang=ja
