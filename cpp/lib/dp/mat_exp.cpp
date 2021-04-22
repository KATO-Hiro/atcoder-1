#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


VVLL mat_exp(VVLL A, ll n, const ll MOD) {
    const ll d = (ll)A.size();
    VVLL B(d, VLL(d, 0)); REP(i,d) B[i][i] = 1;  // 単位行列で初期化

    auto mat_mul = [&](const VVLL& A, const VVLL& B) -> VVLL {
        const ll n1 = (ll)A.size();
        const ll n2 = (ll)B.size();  // = A[0].size()
        const ll n3 = (ll)B[0].size();
        VVLL C(n1, VLL(n3, 0));
        REP(i,n1) REP(k,n2) REP(j,n3) {
            (C[i][j] += A[i][k] * B[k][j]) %= MOD;
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

    ll N, M; cin >> N >> M;

    // Fibonacci
    //   F(1) = 0
    //   F(2) = 1
    //   F(n) = F(n-1) + F(n-2)
    VVLL A = {{1, 1},
              {1, 0}};
    A = mat_exp(A, N-1, M);

    // {F(n+1), F(n)} = A^(n-1) {F(2), F(1)} = A^(n-1) {1, 0}
    // ---> F(n) = A^(n-1)[1][0] * 1 + A^(n-1)[1][1] * 0
    ll ans = A[1][0];
    cout << ans << endl;

    return 0;
}
// Verify: https://yukicoder.me/problems/no/526
