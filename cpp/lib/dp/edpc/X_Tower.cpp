#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
#define MAX(c) *max_element(ALL(c))
using P = pair<ll,ll>;
using VP = vector<P>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------

// NOTE
//   - ナップサック DP
//   - ソートして貪欲

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL w(N),s(N),v(N); REP(i,N) cin >> w[i] >> s[i] >> v[i];

    VP X(N);
    REP(i,N) X[i] = P(s[i] + w[i], i);
    SORT(X);

    // dp[i][j] := i 番目まで見た時に総重量が j である場合の最大価値
    ll M = MAX(s) + MAX(w);
    VVLL dp(N+1, VLL(M+1, 0));
    FOR(i,1,N+1) {
        ll t = X[i-1].second;
        REP(j,M+1) {
            chmax(dp[i][j], dp[i-1][j]);
            if (0 <= j-w[t] && j-w[t] <= s[t]) {
                chmax(dp[i][j], dp[i-1][j-w[t]] + v[t]);
            }
        }
    }
    ll ans = MAX(dp[N]);
    cout << ans << '\n';

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_x
