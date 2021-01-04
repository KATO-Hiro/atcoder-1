#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;
using VVM = vector<VM>;

// NOTE
//   - 貰う DP + 累積和で高速化
//   - 類題: ABC179-D, ABC183-E

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, K; cin >> N >> K;
    VLL A(N+1); FOR(i,1,N+1) cin >> A[i];

    VVM dp(N+1, VM(K+1, 0)); dp[0][0] = 1;
    VM ds(K+2,0);  // 累積和．k=0 にも意味があるので一つ右にズラして使用
    FOR(i,1,N+1) {
        ds[0] = 0;
        FOR(k,1,K+2) ds[k] = ds[k-1] + dp[i-1][k-1];
        FOR(k,0,K+1) dp[i][k] += ds[k+1] - ds[max(0LL,k+1-A[i]-1)];
    }
    ll ans = dp[N][K].val();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_m
