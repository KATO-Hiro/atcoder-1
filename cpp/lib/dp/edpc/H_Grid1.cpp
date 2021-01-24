#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VS = vector<string>;
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;
using VVM = vector<VM>;

// NOTE
//   - グリッド DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, W; cin >> H >> W;
    VS A(H); REP(i,H) cin >> A[i];
 
    // dp[h][w] := (1,1) から (h,w) までの経路数
    VVM dp(H, VM(W,0));
    dp[0][0] = 1;
    REP(h,H) REP(w,W) {
        if (A[h][w] == '#') continue;
        if (0 <= w-1) dp[h][w] += dp[h][w-1];
        if (0 <= h-1) dp[h][w] += dp[h-1][w];
    }
    ll ans = dp[H-1][W-1].val();
    cout << ans << '\n';

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_h
