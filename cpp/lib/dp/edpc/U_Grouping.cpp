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

// NOTE
//   - bit DP
//   - O(3^N)
//   - 部分集合の列挙方法は蟻本 p.144 に記載あり

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL A(N,VLL(N)); REP(i,N) REP(j,N) cin >> A[i][j];

    VLL dp(1<<N,0);
    REP(S,1<<N) {
        // S を1グループにした場合の総得点で初期化
        REP(i,N) if (S & (1<<i)) {
            FOR(j,i+1,N) if (S & (1<<j)) {
                dp[S] += A[i][j];
            }
        }
        // S 内の2グループ分割を全探索 (≒ 区間 DP)
        for (ll T = (S-1) & S; 0 < T; T = (T-1) & S) {
            dp[S] = max(dp[S], dp[T] + dp[T^S]);  // T^S: S における T の補集合 S\T
        }
    }
    ll ans = dp[(1<<N) - 1];
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_u
