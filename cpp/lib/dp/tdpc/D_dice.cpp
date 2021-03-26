#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
using VVVVD = vector<VVVD>;
// --------------------------------------------------------

// NOTE
//   - 確率 DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, D; cin >> N >> D;

    ll f2 = 0; while (D % 2 == 0) { D /= 2; f2++; }
    ll f3 = 0; while (D % 3 == 0) { D /= 3; f3++; }
    ll f5 = 0; while (D % 5 == 0) { D /= 5; f5++; }
    if (D != 1) { cout << 0 << endl; return 0; }

    // dp[i][f2][f3][f5] := サイコロを i 回振ったときの出た目の積について，
    //                      素因数 n が fn 個含まれる状態の確率
    VVVVD dp(N+1,VVVD(f2+1,VVD(f3+1,VD(f5+1,0))));
    dp[0][0][0][0] = 1.0;
    FOR(i,1,N+1) {
        FOR(a,0,f2+1) FOR(b,0,f3+1) FOR(c,0,f5+1) {
            double p = dp[i-1][a][b][c] / 6.0;
            ll a1 = min(a+1,f2);
            ll a2 = min(a+2,f2);
            ll b1 = min(b+1,f3);
            ll c1 = min(c+1,f5);
            dp[i][a ][b ][c ] += p;  // 1
            dp[i][a1][b ][c ] += p;  // 2
            dp[i][a ][b1][c ] += p;  // 3
            dp[i][a2][b ][c ] += p;  // 4
            dp[i][a ][b ][c1] += p;  // 5
            dp[i][a1][b1][c ] += p;  // 6
        }
    }
    double ans = dp[N][f2][f3][f5];
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_dice
