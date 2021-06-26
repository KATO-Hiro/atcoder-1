#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;


// G := [l,r] における subarray sum の最大値
// L := [l,r] における subarray sum の最大値 (a[l] を含む)
// R := [l,r] における subarray sum の最大値 (a[r] を含む)
// S := [l,r] における総和
//   <https://usaco.guide/plat/seg-ext/#solution---subarray-sum-queries>
struct S { ll G, L, R, S; };
S op(S a, S b) {
    ll g = max(max(a.G, b.G), a.R + b.L);
    ll l = max(a.L, a.S + b.L);
    ll r = max(b.R, a.R + b.S);
    ll s = a.S + b.S;
    return S{g, l, r, s};
}
S e() { return S{-INF, -INF, -INF, 0}; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    VLL X(N); REP(i,N) cin >> X[i];

    vector<S> A(N);
    REP(i,N) {
        ll tmp = max(0LL, X[i]);
        A[i] = S{tmp, tmp, tmp, X[i]};
    }
    segtree<S, op, e> seg(A);

    while (Q--) {
        ll k, x; cin >> k >> x;
        k--;

        ll tmp = max(0LL, x);
        seg.set(k, S{tmp, tmp, tmp, x});

        ll ans = seg.all_prod().G;
        cout << ans << '\n';
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1190/
