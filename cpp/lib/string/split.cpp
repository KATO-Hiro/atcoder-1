#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>  // is_any_of


// 文字列 S を sep で区切った vector を返す
// ※ S が半角スペース等で区切られている場合，getline(cin,S) で入力する必要あり
vector<string> split(string& S, string sep) {
    vector<string> T;
    boost::algorithm::split(T, S, boost::is_any_of(sep));
    return T;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; getline(cin, S);

    auto T = split(S, " ");

    vector<char> ans;
    ll N = (ll)T.size();
    for (ll i = 0; i < N; i++) {
        string& s = T[i];
        if (s == "Left") {
            cout << '<';
        } else if (s == "Right") {
            cout << '>';
        } else {
            cout << 'A';
        }
        cout << (i < N-1 ? ' ' : '\n');
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/arc045/tasks/arc045_a
