#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint;
using VM = vector<mint>;
using VVM = vector<VM>;


/**
 * @brief 行列累乗
 *        d x d の正方行列 A に対して A^n を O(k^3 log n) で求める
 * 
 * @tparam T 行列要素の型  e.g.) mint, ll
 * @param A 正方行列
 * @param n 指数
 * @return vector<vector<T>> A^n の計算結果
 */
template<class T>
vector<vector<T>> mat_exp(vector<vector<T>> A, ll n) {
    using VT = vector<T>;
    using VVT = vector<VT>;
    const ll d = (ll)A.size();
    VVT B(d, VT(d, 0)); REP(i,d) B[i][i] = 1;  // 単位行列で初期化

    auto mat_mul = [&](const VVT& A, const VVT& B) -> VVT {
        VVT C(d, VT(d, 0));
        REP(i,d) REP(k,d) REP(j,d) {
            C[i][j] += A[i][k] * B[k][j];
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

    mint::set_mod(M);

    // Fibonacci
    //   F(1) = 0
    //   F(2) = 1
    //   F(n) = F(n-1) + F(n-2)
    VVM A = {{1, 1},
             {1, 0}};
    auto An = mat_exp<mint>(A, N-1);

    // {F(n+1), F(n)} = A^(n-1) {F(2), F(1)} = A^(n-1) {1, 0}
    // ---> F(n) = A^(n-1)[1][0] * 1 + A^(n-1)[1][1] * 0
    ll ans = An[1][0].val();
    cout << ans << endl;

    return 0;
}
// Verify: https://yukicoder.me/problems/no/526
