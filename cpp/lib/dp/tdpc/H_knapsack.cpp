#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define MAX(c) *max_element(ALL(c))
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------

// NOTE
//   - ナップサック DP
//   - 状態削減・マージ等

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, W, C; cin >> N >> W >> C;
    VLL w(N),v(N),c(N);
    VVLL X(50);
    REP(i,N) {
        cin >> w[i] >> v[i] >> c[i];
        X[c[i]-1].push_back(i);
    }

    // dp[i][j] := i 色使って重さが j のときの価値の最大値
    VVLL dp(C+1,VLL(W+1,0));
    for (auto& XX : X) {
        RFOR(i,1,C+1) {
            // i-1 色使った場合の結果に 1 色追加した場合のナップサック問題
            VLL dpp(dp[i-1]);
            for (ll x : XX) {
                RREP(j,W+1) {
                    if (0 <= j-w[x]) chmax(dpp[j], dpp[j-w[x]] + v[x]);
                }
            }
            RREP(j,W+1) {
                chmax(dp[i][j], dpp[j]);
            }
        }
    }
    ll ans = 0;
    REP(i,C+1) REP(j,W+1) chmax(ans, dp[i][j]);
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_knapsack
