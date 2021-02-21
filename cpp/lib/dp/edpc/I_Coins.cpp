#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
using VD = vector<double>;
using VVD = vector<VD>;
// --------------------------------------------------------

// NOTE
//   - 確率 DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VD P(N+1); FOR(i,1,N+1) cin >> P[i];

    // dp[i][j] := i 番目までコインを見た時に j 枚が表である確率
    VVD dp(N+1, VD(N+1, 0));
    dp[0][0] = 1.0;
    FOR(i,1,N+1) FOR(j,0,i+1) {
        dp[i][j] += dp[i-1][j] * (1 - P[i]);
        if (0 <= j-1) dp[i][j] += dp[i-1][j-1] * P[i];
    }
 
    double ans = 0.0;
    FOR(j,N/2+1,N+1) ans += dp[N][j];
    cout << ans << '\n';

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_i
