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

    ll q, s, t, x, i;
    while (Q--) {
        cin >> q;
        if (q == 0) {
            cin >> s >> t >> x;
            s--; t--;
            seg.apply(s, t + 1, F{x});
        } else {
            cin >> i;
            i--;
            cout << seg.get(i) << '\n';
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja
