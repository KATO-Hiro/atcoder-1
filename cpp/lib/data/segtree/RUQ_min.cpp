#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間更新(最小値更新)・1点取得
using S = ll;
struct F { ll x; };
S op([[maybe_unused]] S a, [[maybe_unused]] S b) { return 0; }
S e() { return 0; }
S mapping(F f, S x) { return min(f.x, x); }
F composition(F f, F g) { return F{min(f.x, g.x)}; }
F id() { return F{INF}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    VLL A(N+1, N);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg_H(A);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg_W(A);

    ll ans = (N-2)*(N-2);
    while (Q--) {
        ll q, x; cin >> q >> x;
        if (q == 1) {
            ll h = seg_H.get(x);
            ans -= (h - 2);
            seg_W.apply(1, h, F{x});
        } else if (q == 2) {
            ll w = seg_W.get(x);
            ans -= (w - 2);
            seg_H.apply(1, w, F{x});
        }
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc179/tasks/abc179_f
