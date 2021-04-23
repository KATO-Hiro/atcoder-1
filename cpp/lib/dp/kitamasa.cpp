#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
#define CLZ(b) __builtin_clzll(b)
#define BITLEN(b) (64LL - CLZ(b))
static const ll MOD = 1000000007;
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;


// References:
//   <https://tjkendev.github.io/procon-library/cpp/series/kitamasa.html>
//   <https://yosupo.hatenablog.com/entry/2015/03/27/025132>

/**
 * @brief Kitamasa 法
 *        線形漸化式における A[n] を O(k^2 log n) で求める
 *          - 線形漸化式: A[n+k] = C[n]*A[n] + C[n+1]*A[n+1] + ... + C[n+k-1]*A[n+k-1]
 *          - 初期条件  : { A[0], A[i], ... , A[k-1] }
 *            --> 数列 A における第 1 〜 k 項の値そのもの
 * 
 * @tparam T 数列要素の型  e.g.) mint, ll
 */
template <class T>
struct Kitamasa {
    ll K;
    vector<T> A, C;
    Kitamasa(const vector<T>& A_, const vector<T>& C_) : A(A_), C(C_) {
        assert(A.size() == C.size());
        K = (ll)A.size();
    }

    // C(N,*) -> C(N+1,*)
    vector<T> nxt(const vector<T>& C0) {
        vector<T> C1(K); C1[0] = C0[K-1] * C[0];
        FOR(i,1,K) C1[i] = C0[i-1] + C0[K-1] * C[i];
        return C1;
    }

    // C(N,*) -> C(2N,*)
    vector<T> dbl(const vector<T>& C0) {
        vector<vector<T>> CC(K); CC[0] = C0;
        vector<T> C1(K,0);
        FOR(i,1,K) CC[i] = nxt(CC[i-1]);
        REP(i,K) REP(j,K) C1[i] += C0[j] * CC[j][i];
        return C1;
    }

    // A[n] を求める
    // NOTE: 数列 A の m 番目の項を求める場合は m-1 を指定する
    T solve(ll n) {
        assert(0 <= n);
        if (n <= K-1) return A[n];

        vector<T> C1(K,0); C1[0] = 1;
        ll b = BITLEN(n);
        while (b--) {
            C1 = dbl(C1);
            if (BIT(n,b)) C1 = nxt(C1);
        }

        T res = 0;
        REP(i,K) res += C1[i] * A[i];
        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll K, N; cin >> K >> N;

    VM A(K,1), C(K,1);
    Kitamasa<mint> kit(A, C);

    ll ans = kit.solve(N-1).val();
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci
