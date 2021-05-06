#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間加算・1点取得
using S = ll;
struct F { ll x; };
S op([[maybe_unused]] S a, [[maybe_unused]] S b) { return 0; }
S e() { return 0; }
S mapping(F f, S a) { return a + f.x; }
F composition(F f, F g) { return F{f.x + g.x}; }
F id() { return F{0}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, Q; cin >> N >> Q;
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(N);

    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll s, t, x; cin >> s >> t >> x;
            s--; t--;
            seg.apply(s, t + 1, F{x});
        } else {
            ll i; cin >> i;
            i--;
            cout << seg.get(i) << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja
