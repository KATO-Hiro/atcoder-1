#include <bits/stdc++.h>
#include <boost/algorithm/string/replace.hpp>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


// https://atcoder.jp/contests/arc019/tasks/arc019_1
int main() {
    string S;
    cin >> S;
    boost::replace_all(S, "O", "0");
    boost::replace_all(S, "D", "0");
    boost::replace_all(S, "I", "1");
    boost::replace_all(S, "Z", "2");
    boost::replace_all(S, "S", "5");
    boost::replace_all(S, "B", "8");
    cout << S << endl;
    return 0;
}