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


int lcs(string X, string Y) {
    ll N = SZ(X);
    ll M = SZ(Y);
    X = " " + X;
    Y = " " + Y;

    VVLL dp(N + 1, VLL(M + 1, 0));
    FOR(i, 1, N + 1) FOR(j, 1, M + 1) {
        if (X[i] == Y[j]) {
            dp[i][j] = dp[i-1][j-1] + 1;
        } else {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[N][M];
}


// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int Q; cin >> Q;
    REP(_, Q) {
        string X; cin >> X;
        string Y; cin >> Y;
        cout << lcs(X, Y) << '\n';
    }

    return 0;
}
