#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/string>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    string T; cin >> T;

    ll N = S.size();
    ll M = T.size();

    vector<int> sa = suffix_array(S);

    VLL ans;
    REP(i,N) {
        if (S.compare(sa[i], M, T) == 0) ans.push_back(sa[i]);
    }
    SORT(ans);
    for (ll a : ans) {
        cout << a << '\n';
    }


    return 0;
}
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja
