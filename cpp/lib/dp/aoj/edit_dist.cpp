#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S1; cin >> S1;
    string S2; cin >> S2;

    ll A = SZ(S1);
    ll B = SZ(S2);
    S1 = " " + S1;
    S2 = " " + S2;

    VVLL dp(A+1, VLL(B+1,INF));
    dp[0][0] = 0;
    REP(a,A+1) REP(b,B+1) {
        if (0 <= a-1) chmin(dp[a][b], dp[a-1][b] + 1);
        if (0 <= b-1) chmin(dp[a][b], dp[a][b-1] + 1);
        if (0 <= a-1 && 0 <= b-1) chmin(dp[a][b], dp[a-1][b-1] + (S1[a] == S2[b] ? 0 : 1));
    }
    cout << dp[A][B] << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E&lang=ja
