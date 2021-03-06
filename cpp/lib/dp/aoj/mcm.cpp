#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N; cin >> N;
    VLL p(N + 1); REP(i,N) cin >> p[i] >> p[i + 1];

    VVLL dp(N + 1, VLL(N + 1, INF));
    REP(i, N + 1) dp[i][i] = 0;
    FOR(l, 2, N + 1) {
        FOR(i, 1, N + 1 - (l - 1)) {
            ll j = i + l - 1;
            FOR(k, i, j) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + p[i-1] * p[k] * p[j]);
            }
        }
    }
    cout << dp[1][N] << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_B
