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


// 最長共通部分列 (LCS: Longest Common Subsequence)
//   ※ 破壊的メソッド (文字列の先頭に " " (半角スペース) が追加される)
ll lcs(string& X, string& Y) {
    const ll N = SZ(X);
    const ll M = SZ(Y);
    X = " " + X;
    Y = " " + Y;
    VVLL dp(N+1, VLL(M+1, 0));
    FOR(i,1,N+1) FOR(j,1,M+1) {
        if (X[i] == Y[j]) {
            dp[i][j] = dp[i-1][j-1] + 1;
        } else {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[N][M];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll Q; cin >> Q;
    while (Q--) {
        string X; cin >> X;
        string Y; cin >> Y;
        cout << lcs(X, Y) << '\n';
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C&lang=ja
