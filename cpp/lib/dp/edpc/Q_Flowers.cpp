#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点更新・区間取得
using S = ll;
S op(S a, S b) { return max(a, b); }
S e() { return 0; }

// NOTE
//   - インライン DP
//   - セグメント木
//   - LIS の派生問題
//   - 蟻本 p.186 が類題

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL H(N); REP(i,N) cin >> H[i];
    VLL A(N); REP(i,N) cin >> A[i];

    // seg[h] := 最後の花の高さが h となる単調増加列における美しさの総和の最大値
    segtree<S, op, e> seg(N+1);
    REP(i,N) {
        seg.set(H[i], seg.prod(0, H[i]) + A[i]);  // LIS のように更新
    }
    ll ans = seg.all_prod();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_q
