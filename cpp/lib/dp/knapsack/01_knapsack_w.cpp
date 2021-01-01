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
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, W; cin >> N >> W;
    VLL w(N+1),v(N+1); FOR(i,1,N+1) cin >> w[i] >> v[i];

    VVLL dp(N+1, VLL(W+1, 0));
    FOR(i,1,N+1) FOR(j,0,W+1) {
        if (0 <= j - w[i]) {
            dp[i][j] = max(dp[i-1][j], dp[i-1][j - w[i]] + v[i]);
        } else {
            dp[i][j] = dp[i-1][j];
        }
    }
    cout << MAX(dp[N]) << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/dp/tasks/dp_d
