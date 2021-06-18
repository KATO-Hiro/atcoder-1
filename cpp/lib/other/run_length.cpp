#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------

// ランレングス圧縮
// e.g.) <S,T> = <string,char>, <vector<ll>,ll>
template<class S, class T>
vector<pair<T,ll>> run_length(const S& A) {
    ll const N = (ll)A.size();
    vector<pair<T,ll>> R;
    ll i = 0;
    while (i < N) {
        T x = A[i];
        ll n = 1;
        while (i+1 < N && A[i+1] == x) {
            n++; i++;
        }
        R.push_back(make_pair(x, n));
        i++;
    }
    return R;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;

    auto R = run_length<string, char>(S);
    // auto R = run_length<VLL, ll>(A);
    for (auto& m : R) {
        cout << m.first << m.second;
    }
    cout << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc019/tasks/abc019_2
