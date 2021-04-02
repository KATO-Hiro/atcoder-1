#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

// NOTE
//   - 貰う DP + 累積和と累積 max で高速化

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL F(N+1,VLL(N+1)); FOR(i,1,N+1) FOR(j,1,N+1) cin >> F[i][j];

    // dp[i][j] := i 番目まで見たときの i 番目の猫から距離 1 以内にいる
    //             最も左の猫が j (< i) 番目の場合の幸福度の最大値
    // ds[i]    := i 番目まで見たときの幸福度の最大値
    VVLL dp(N+1,VLL(N+1,-INF)); dp[1][1] = 0;
    VLL sum(N+1);  // sum[j] = Σ_{k=j->i}{f_ki} : 猫 i からの幸福度の累積和
    FOR(i,1,N+1) {
        sum[i] = F[i][i];  // = 0
        RFOR(j,1,i) sum[j] = sum[j+1] + F[j][i];
        ll max_dp = -INF;  // 猫 i-1 まで見たときの dp の累積 max (1 -> i-1)
        FOR(j,1,i+1) {
            if (j <= i-1) chmax(max_dp, dp[i-1][j]);
            chmax(dp[i][j], max_dp + sum[j]);
        }
    }
    ll ans = -INF;
    FOR(j,1,N+1) chmax(ans, dp[N][j]);
    cout << (2 * ans) << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_cat
