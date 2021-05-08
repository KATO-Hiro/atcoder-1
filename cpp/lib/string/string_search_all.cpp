#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/string>
using namespace atcoder;


/**
 * @brief 文字列 S 中での文字列 T の出現箇所を全探索する (z_algorithm)
 *        - O(|S|+|T|)
 * 
 * @param S 文字列 S
 * @param T 文字列 T
 * @return VLL 文字列 S における文字列 T の出現位置の配列
 */
VLL string_search_all(const string& S, const string& T) {
    const ll N = S.size();
    const ll M = T.size();

    string X = T + '$' + S;
    auto za = z_algorithm(X);

    VLL res;
    REP(i,N) {
        if (za[M + 1 + i] == M) res.push_back(i);
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    string T; cin >> T;

    auto match = string_search_all(S, T);
    for (ll i : match) {
        cout << i << '\n';
    }

    return 0;
}
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja
