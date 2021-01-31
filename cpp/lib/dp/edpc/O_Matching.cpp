#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) ((b>>i) & 1)
#define PCNT(b) __builtin_popcountll(b)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;
using VVM = vector<VM>;

// NOTE
//   - bit DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL A(N, VLL(N)); REP(i,N) REP(j,N) cin >> A[i][j];

    // dp[S] := S[i]=1の女性にペアが存在する場合の数
    VM dp(1<<N, 0);
    dp[0] = 1;
    FOR(S,1,1<<N) {
        ll i = PCNT(S);  // 何人目の男性か
        REP(j,N) if (BIT(S,j)) {
            if (A[i-1][j] == 0) continue;
            dp[S] += dp[S - (1<<j)];
        }
    }
    ll ans = dp[(1<<N) - 1].val();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_o
