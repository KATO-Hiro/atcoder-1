#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VB = vector<bool>;
using VVB = vector<VB>;
// --------------------------------------------------------

// NOTE
//   - ナップサック DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL P(N+1); FOR(i,1,N+1) cin >> P[i];

    ll M = 100;

    // dp[i][j] := i番目までの問題から何問か解いたとき得点jが得られるか
    VVB dp(N+1, VB(N*M+1,false));
    dp[0][0] = true;
    FOR(i,1,N+1) FOR(j,0,N*M+1) {
        if (0 <= j - P[i]) {
            dp[i][j] = dp[i-1][j] | dp[i-1][j - P[i]];
        } else {
            dp[i][j] = dp[i-1][j];
        }
    }
    ll ans = 0;
    REP(i,N*M+1) if (dp[N][i]) ans++;
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_contest
