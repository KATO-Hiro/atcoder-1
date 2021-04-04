#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll MOD = 1000000007;
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;
using VVM = vector<VM>;

// NOTE
//   - bit DP
//   - 行列累乗 + 繰り返し二乗法

VVLL mat_exp(VVLL A, ll n, const ll MOD) {
    const ll d = (ll)A.size();
    VVLL B(d, VLL(d, 0)); REP(i,d) B[i][i] = 1;  // 単位行列で初期化

    auto mat_mul = [&](VVLL& A, VVLL& B) -> VVLL {
        const ll n1 = (ll)A.size();
        const ll n2 = (ll)B.size();  // = A[0].size()
        const ll n3 = (ll)B[0].size();
        VVLL C(n1, VLL(n3, 0));
        REP(i,n1) REP(k,n2) REP(j,n3) {
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
        }
        return C;
    };

    // e.g.) n = 11, B = A^(2^3) + A^(2^1) + A^(2^0)  (11 = 2^3 + 2^1 + 2^0)
    while (n > 0) {
        if (n & 1) B = mat_mul(B, A);  // 欲しいタイミングで拾う
        A = mat_mul(A, A);
        n >>= 1;
    }
    return B;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, R; cin >> H >> R;
    VVLL G(R, VLL(R)); REP(i,R) REP(j,R) cin >> G[i][j];

    // A[i][j] := 1 階分降りた時の部屋 i から部屋 j への経路の個数
    VVLL A(R,VLL(R,0));
    VVM dp(1<<R,VM(R));
    REP(s,R) {
        REP(S,1<<R) REP(u,R) dp[S][u] = 0;
        dp[1<<s][s] = 1;
        REP(S,1<<R) {
            REP(u,R) if (BIT(S,u)) {
                REP(v,R) if (!BIT(S,v) && G[u][v]) {
                    dp[S | (1<<v)][v] += dp[S][u];
                }
            }
            REP(v,R) {
                (A[s][v] += dp[S][v].val()) %= MOD;
            }
        }
    }

    // A[i][j] := H-1 階分降りた時の部屋 i から部屋 j への経路の個数
    A = mat_exp(A, H, MOD);
    ll ans = A[0][0];
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_house
