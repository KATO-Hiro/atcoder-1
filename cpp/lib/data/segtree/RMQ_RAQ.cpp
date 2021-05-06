#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間加算・区間最小
using S = ll;
struct F { ll x; };
S op(S a, S b) { return min(a, b); }
S e() { return INF; }
S mapping(F f, S a) { return a + f.x; }
F composition(F f, F g) { return F{f.x + g.x}; }
F id() { return F{0}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, Q; cin >> N >> Q;
    VLL A(N, 0);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll s, t, x; cin >> s >> t >> x;
            seg.apply(s, t + 1, F{x});
        } else {
            ll s, t; cin >> s >> t;
            cout << seg.prod(s, t + 1) << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H&lang=ja
