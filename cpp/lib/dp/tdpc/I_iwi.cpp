#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------

// NOTE
//   - 区間 DP
//   - 連鎖行列積の構造 + α
//   - 類題: past202012_l

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    ll N = SZ(S);

    // dp[l][r] := 部分文字列 S[l,r) から消去できる iwi の総文字数の最大値
    //             ※ r は右半開区間
    VVLL dp(N+1,VLL(N+1,0));
    FOR(k,1,N+1) REP(l,N-k+1) {  // k は部分文字列 S[l,r) の長さ
        ll r = l + k;

        // S[l,m), S[m,r) を独立に操作するケース
        FOR(m,l+1,r) chmax(dp[l][r], dp[l][m] + dp[m][r]);

        // S[l,r) = "i...w...i" のケース (... 部が完全に消せる場合のみ考慮すれば十分)
        if (S[l] == 'i' && S[r-1] == 'i') {
            FOR(m,l+1,r-1) if (S[m] == 'w') {
                if (dp[l+1][m] == m-(l+1) && dp[m+1][r-1] == (r-1)-(m+1)) {
                    chmax(dp[l][r], r-l);
                }
            }
        }
    }

    ll ans = dp[0][N] / 3;  // 操作回数なので 3 で割る
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_iwi
