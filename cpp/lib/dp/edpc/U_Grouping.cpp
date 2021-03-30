#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
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

    // dp[S] := 状態 S に対応するうさぎたちをグループ分けした時の総得点の最大値
    VLL dp(1<<N,0);
    REP(S,1<<N) {
        // S を 1 グループにした場合の総得点で dp[S] を初期化
        REP(i,N) if (BIT(S,i)) {
            FOR(j,i+1,N) if (BIT(S,j)) {
                dp[S] += A[i][j];
            }
        }
        // S における 2 グループ分割の方法を全探索 (≒ 区間 DP)
        //    <https://kyopro-friends.hatenablog.com/entry/2019/01/12/231106>
        for (ll T = (S-1) & S; 0 < T; T = (T-1) & S) {
            chmax(dp[S], dp[T] + dp[T^S]);  // T^S: S における T の補集合 S\T
        }
    }
    ll ans = dp[(1<<N) - 1];
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_u
