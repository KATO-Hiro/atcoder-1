#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/fenwicktree>
using namespace atcoder;

/**
 * @brief 座標圧縮
 *        e.g.) X = {3, 3, 1, 6, 1}
 *             ---------------------
 *              X = {1, 1, 0, 2, 0}
 *             ZX = {1, 3, 6}
 * 
 * @param X 座標配列の参照 (圧縮後の座標に書き換えられる)
 * @return VLL 圧縮前の座標配列 (圧縮後の座標と1対1対応)
 */
VLL compress(VLL& X) {
    const ll N = SZ(X);
    VLL XS(X);  // 圧縮前の座標配列 (圧縮後の座標と1対1対応)

    // 重複削除
    SORT(XS);
    XS.erase(unique(ALL(XS)), XS.end());

    // 圧縮後の座標の割り当て
    REP(i,N) {
        X[i] = lower_bound(ALL(XS), X[i]) - XS.begin();
    }
    return XS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL A(N); REP(i,N) cin >> A[i];

    compress(A);  // A が順列であれば不要
    fenwick_tree<ll> fw(N);  // 1 <= A[i] <= N であれば fw(N+1) にする
    ll num = 0;
    REP(i,N) {
        num += i - fw.sum(0, A[i]);
        fw.add(A[i], 1);
    }
    cout << num << endl;

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D&lang=ja
