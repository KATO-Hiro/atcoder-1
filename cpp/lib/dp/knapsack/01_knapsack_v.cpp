#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define MAX(c) *max_element(ALL(c))
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, W; cin >> N >> W;
    VLL w(N+1),v(N+1); FOR(i,1,N+1) cin >> w[i] >> v[i];

    ll V = N * MAX(v);
    VVLL dp(N+1, VLL(V+1, INF));
    dp[0][0] = 0;
    FOR(i,1,N+1) FOR(j,0,V+1) {
        if (0 <= j - v[i]) {
            dp[i][j] = min(dp[i-1][j], dp[i-1][j - v[i]] + w[i]);
        } else {
            dp[i][j] = dp[i-1][j];
        }
    }
    ll ans = 0;
    FOR(i,0,V+1) if (dp[N][i] <= W) chmax(ans, i);
    cout << ans << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/dp/tasks/dp_e
