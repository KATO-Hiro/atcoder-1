#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間更新・1点取得
using S = ll;
struct F { ll x; };
S op([[maybe_unused]] S a, [[maybe_unused]] S b) { return 0; }
S e() { return 0; }
S mapping(F f, S x) { return (f.x == INF) ? x : f.x; }
F composition(F f, F g) { return (f.x == INF) ? g : f; }
F id() { return F{INF}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, Q; cin >> N >> Q;
    VLL A(N, (1LL << 31) - 1);  // 問題文「a_i は 2^31 - 1 で初期化」
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll s, t, x; cin >> s >> t >> x;
            seg.apply(s, t + 1, F{x});
        } else {
            ll i; cin >> i;
            cout << seg.get(i) << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
