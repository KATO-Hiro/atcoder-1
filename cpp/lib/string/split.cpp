#include <bits/stdc++.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>  // is_any_of
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


// https://atcoder.jp/contests/arc045/tasks/arc045_a
int main() {
    string S;
    getline(cin, S);

    vector<string> T;
    boost::algorithm::split(T, S, boost::is_any_of(" "));

    vector<char> ans;
    for (string s : T) {
        if (s == "Left") {
            ans.push_back('<');
        } else if (s == "Right") {
            ans.push_back('>');
        } else {
            ans.push_back('A');
        }

    }

    for (int i = 0; i < ans.size() - 1; i++) {
        cout << ans[i] << " ";
    }
    cout << ans.back() << endl;

    return 0;
}