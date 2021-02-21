#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------

// NOTE
//   - LCS
//   - 復元

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    string T; cin >> T;

    ll N = SZ(S);
    ll M = SZ(T);
    S = " " + S;
    T = " " + T;

    // dp[l][r] := S(1,l) と T(1,r) における最長共通部分列の長さ
    VVLL dp(N+1, VLL(M+1, 0));
    FOR(i,1,N+1) FOR(j,1,M+1) {
        if (S[i] == T[j]) {
            dp[i][j] = dp[i-1][j-1] + 1;
        } else {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    // LCS 復元
    // LCS の長さ len = dp[N][M] だけ後ろから探索
    //   - S[i] == T[j] の場合，(i,j) は (i-1,j-1) へ遷移
    //   - S[i] != T[j] の場合，dp[i-1][j] と dp[i][j-1] の長さを確認して
    //     dp[i][j] の長さが維持される方へ遷移: (i-1,j) or (i,j-1)
    //     --> 長さが変化すると LCS の復元に必要な文字を飛ばしてしまうため
    //         (言い換えると，LCS に使われない文字を飛ばすように遷移する)
    ll len = dp[N][M], i = N, j = M;
    string ans = string(len, ' ');
    while (len > 0) {
        if (S[i] == T[j]) {
            ans[--len] = S[i];
            i--; j--;
        } else if (dp[i][j] == dp[i-1][j]) {
            i--;
        } else {  // dp[i][j] == dp[i][j-1]
            j--;
        }
    }
    cout << ans << '\n';

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_f
