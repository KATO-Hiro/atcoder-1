#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;
using VVM = vector<VM>;

// NOTE
//   - 挿入 DP に似た何か

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    string S; cin >> S;
    S = " " + S;

    // dp[i][j] := i番目まで決めた時，i番目の数より大きい数がj個残っている場合の数
    VVM dp(N+1, VM(N,0));
    FOR(j,0,N) dp[1][j] = 1;
    FOR(i,2,N+1) {
        VM T(N+1,0);  // 累積和の計算都合でインデックスは実際の数に1加えたものが対応
        FOR(j,0,N-i+2) T[j+1] += T[j] + dp[i-1][j];
        if (S[i-1] == '<') {
            // FOR(j,0,N-i+1) FOR(k,j+1,N-i+2) dp[i][j] += dp[i-1][k];
            FOR(j,0,N-i+1) dp[i][j] += T[N-i+2] - T[j+1];
        } else {  // >
            // FOR(j,0,N-i+1) FOR(k,0,j+1) dp[i][j] += dp[i-1][k];
            FOR(j,0,N-i+1) dp[i][j] += T[j+1] - T[0];
        }
    }
    ll ans = dp[N][0].val();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_t
