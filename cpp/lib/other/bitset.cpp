#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------

// ランレングス圧縮
// e.g.) <S,T> = <string,char>, <vector<ll>,ll>
template<class S, class T>
vector<pair<T,ll>> run_length(S& A) {
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

// Reference:
//   C++  : <https://cpprefjp.github.io/reference/bitset/bitset.html>
//   APG4b: <https://atcoder.jp/contests/apg4b/tasks/APG4b_ac>

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    ll x, y; cin >> x >> y;

    auto R = run_length<string, char>(S);
    ll N = (ll)R.size();

    const ll shift = 8000;
    bitset<16001> X, Y;
    X[0 + shift] = 1;
    Y[0 + shift] = 1;
    ll m = 0;  // x: 0, y: 1
    REP(i,N) {
        auto& [c, n] = R[i];
        if (i == 0 && c == 'F') {
            X = (X << n);
            continue;
        }
        if (c == 'T') {
            if (n % 2 == 1) m ^= 1;
        } else {
            if (m == 0) {
                X = (X << n) | (X >> n);
            } else {
                Y = (Y << n) | (Y >> n);
            }
        }
    }

    string ans = (X[x + shift] && Y[y + shift] ? "Yes" : "No");
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc082/tasks/arc087_b
