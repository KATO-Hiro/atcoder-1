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
using VVVM = vector<VVM>;

// NOTE
//   - 桁 DP
//   - 類題: tdpc_number (全く同じ)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string K; cin >> K;
    ll D; cin >> D;

    ll L = (ll)K.size();
    K = " " + K;

    // dp[i][j][r] := 上位から i 桁目まで見たとき
    //                K 未満フラグが j で桁和の余りが r の場合の数
    VVVM dp(L + 1, VVM(2, VM(D, 0)));
    dp[0][0][0] = 1;
    FOR(i, 1, L + 1) {
        ll n = K[i] - '0';
        REP(j, 2) {
            ll max_d = (j == 1) ? 9 : n;
            REP(d, max_d + 1) {
                REP(r, D) {
                    dp[i][j | (d < n)][(r + d) % D] += dp[i - 1][j][r];
                }
            }
        }
    }
    // 0 は D の倍数であるため 1 を引いておく
    ll ans = (dp[L][0][0] + dp[L][1][0] - 1).val();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_s
