#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点加算・区間総和
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, Q; cin >> N >> Q;
    segtree<S, op, e> seg(N);

    ll q, x, y;
    while (Q--) {
        cin >> q >> x >> y;
        if (q == 0) {
            x--;
            seg.set(x, seg.get(x) + y);
        } else {
            x--; y--;
            cout << seg.prod(x, y + 1) << '\n';
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=ja
