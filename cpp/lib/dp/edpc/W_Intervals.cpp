#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間加算・区間最大
using S = ll;
struct F { ll x; };
S op(S a, S b) { return max(a, b); }
S e() { return 0; }
S mapping(F f, S a) { return a + f.x; }
F composition(F f, F g) { return F{f.x + g.x}; }
F id() { return F{0}; }

// NOTE
//   - インライン DP
//   - 遅延セグメント木

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    vector<tuple<ll,ll,ll>> A(M);  // (r, l, a)
    REP(i,M) {
        ll l, r, a; cin >> l >> r >> a;
        A[i] = {r, l, a};
    }
    SORT(A);
    ll k = 0;

    // seg[j] := (i 文字目まで見て) 最後の 1 が j 文字目となる文字列の最大スコア
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(N+1);
    FOR(i,1,N+1) {
        // i 文字目まで見た時の最大スコア (このとき i 文字目は 0 のみ考慮)
        seg.set(i, seg.prod(0, i));

        // r[k] = i となる各区間 k に対して j ∈ [l[k], i] を満たす j の範囲に a[k] を加算
        while (k < M) {
            auto [r, l, a] = A[k];
            if (i != r) break;
            k++;
            seg.apply(l, r+1, F{a});
        }
    }
    ll ans = seg.all_prod();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_w
