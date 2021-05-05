#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#include <atcoder/string>
using namespace atcoder;


/**
 * @brief 接尾辞配列を用いた文字列検索
 *        文字列 S 中での文字列 T の出現を検索する
 *        - O(|T| log|S|)
 *        - 接尾辞配列には空文字が含まれないことを想定 (ACL 準拠)
 * 
 * @param S 文字列 S
 * @param sa 文字列 S の接尾辞配列
 * @param T 文字列 T
 * @return true 文字列 S 中に文字列 T が見つかった場合
 * @return false 見つからなかった場合
 */
bool string_search(const string& S, const vector<int>& sa, const string& T) {
    assert(S.size() == sa.size());
    int ng = -1, ok = S.size() - 1;
    while (ok - ng > 1) {
        int m = (ok + ng) / 2;
        (S.compare(sa[m], T.size(), T) >= 0 ? ok : ng) = m;
    }
    return S.compare(sa[ok], T.size(), T) == 0;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    ll Q; cin >> Q;

    vector<int> sa = suffix_array(S);

    while (Q--) {
        string T; cin >> T;
        ll ans = (string_search(S,sa,T) ? 1 : 0);
        cout << ans << '\n';
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D&lang=ja
