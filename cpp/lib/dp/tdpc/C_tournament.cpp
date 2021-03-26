#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VD = vector<double>;
using VVD = vector<VD>;
// --------------------------------------------------------

// NOTE
//   - 確率 DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll K; cin >> K;
    ll N = (1LL<<K);
    VLL R(N); REP(i,N) cin >> R[i];

    // dp[k][i] := 第 k ラウンドで i 番目の人が勝ち残る確率
    VVD dp(K+1,VD(N,0));
    REP(i,N) dp[0][i] = 1.0;

    FOR(k,1,K+1) REP(i,N) {
        ll kk = (1LL<<(k-1));
        ll q = i / kk;  // k ラウンド目で i が属する部分トーナメント ID (0-index)
        ll r = (q % 2 == 0 ? q+1 : q-1);  // 対戦相手が属する部分トーナメント ID (0-index)
        FOR(j,kk*r,kk*(r+1)) {
            double p = 1.0 / (1.0 + pow(10.0, (R[j] - R[i])/400.0));
            dp[k][i] += dp[k-1][j] * p;
        }
        dp[k][i] *= dp[k-1][i];
    }
    REP(i,N) cout << dp[K][i] << '\n';

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_tournament
