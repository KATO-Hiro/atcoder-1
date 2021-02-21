#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll MOD = 1000000007;
// --------------------------------------------------------

// NOTE
//   - 行列累乗 + 繰り返し二乗法
//   - 蟻本 p.183 と同じ

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

    ll N, K; cin >> N >> K;
    VVLL A(N, VLL(N)); REP(i,N) REP(j,N) cin >> A[i][j];

    // A[i][j] := 頂点 i から頂点 j への長さ K の有向パスの場合の数
    A = mat_exp(A, K, MOD);
    ll ans = 0;
    REP(i,N) REP(j,N) ans = (ans + A[i][j]) % MOD;
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_r
