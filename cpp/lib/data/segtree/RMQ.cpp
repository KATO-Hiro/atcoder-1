#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点更新・区間最小
using S = ll;
S op(S a, S b) { return min(a, b); }
S e() { return INF; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, Q; cin >> N >> Q;
    VLL A(N, (1LL << 31) - 1);  // 問題文「a_i は 2^31 - 1 で初期化」
    segtree<S, op, e> seg(A);

    while (Q--) {
        ll q, x, y; cin >> q >> x >> y;
        if (q == 0) {
            seg.set(x, y);
        } else {
            cout << seg.prod(x, y + 1) << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=ja
