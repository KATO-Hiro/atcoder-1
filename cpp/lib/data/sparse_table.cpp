#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define CLZ(b) __builtin_clzll(b)
#define BITLEN(b) (64LL - CLZ(b))
using VLL = vector<ll>;
// --------------------------------------------------------


// References:
//   <https://cp-algorithms.com/data_structures/sparse-table.html>
//   <http://tookunn.hatenablog.com/entry/2016/07/13/211148>
//   <https://ikatakos.com/pot/programming_algorithm/data_structure/sparse_table>

/**
 * @brief Sparse Table
 *        結合律と冪等律を満たす代数構造で使用可能 (min/max/gcd/lcm 等)
 * 
 * @tparam S 代数構造の型
 * @tparam (*op)(S,S) 二項演算
 */
template <class S, S (*op)(S, S)>
struct SparseTable {
    ll N, K;
    vector<vector<S>> st;
    SparseTable(ll n, const vector<S>& A) : N(n) {
        K = BITLEN(N) - 1;  // = floor(log2(N))
        st.resize(N);
        REP(i,N) {
            st[i].resize(K+1);
            st[i][0] = A[i];
        }
        // preprocess
        FOR(k,1,K+1) REP(i,N-(1<<k)+1) {
            st[i][k] = op(st[i][k-1], st[i + (1<<(k-1))][k-1]);
        }
    }

    // [l,r)
    S query(ll l, ll r) {
        assert(0 <= l && l < r && r <= N);
        ll k = BITLEN(r-l) - 1;
        return op(st[l][k], st[r - (1<<k)][k]);
    }
};

using S = ll;
S op(S a, S b) { return min(a, b); };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    VLL A(N); REP(i,N) cin >> A[i];

    SparseTable<S,op> st(N,A);

    while (Q--) {
        ll l, r; cin >> l >> r;
        cout << st.query(l, r) << '\n';
    }

    return 0;
}
// Verify: https://judge.yosupo.jp/problem/staticrmq
