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

// NOTE
//   - 貰う DP + 累積和で高速化

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, K; cin >> N >> K;

    // dp[i] := i 番目の駅を通過する場合の数（ただし K 駅連続で停車しない）
    VM dp(N+1,0); dp[0] = 1; dp[1] = 0;
    mint sum = 1;
    FOR(i,2,N) {
        if (0 <= i-K-1) sum -= dp[i-K-1];
        sum += dp[i-1];
        dp[i] = sum;
    }
    mint ans = 0;
    FOR(i,1,K) ans += dp[N-i];
    cout << ans.val() << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_semiexp
