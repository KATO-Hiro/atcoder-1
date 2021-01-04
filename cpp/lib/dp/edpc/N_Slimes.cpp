#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

// NOTE
//   - 区間DP
//   - 連鎖行列積と同じ構造

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL A(N+1); FOR(i,1,N+1) cin >> A[i];

    // dp[l][r] := 区間[l,r]のスライムを1匹にする場合の最小コスト
    VVLL dp(N+1, VLL(N+1, INF)); FOR(i,1,N+1) dp[i][i] = 0;
    VLL S(N+1,0); FOR(i,1,N+1) S[i] = S[i-1] + A[i];
    FOR(w,2,N+1) {  // 区間幅
        FOR(l,1,N-(w-1)+1) {
            ll r = l + (w-1);
            FOR(k,l,r) {  // 区間[l,r]における区切り位置
                chmin(dp[l][r], dp[l][k] + dp[k+1][r] + (S[r] - S[l-1]));
            }
        }
    }
    ll ans = dp[1][N];
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_n
