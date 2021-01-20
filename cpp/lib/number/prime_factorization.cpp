#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


map<ll,ll> prime_factorization(ll n) {
    map<ll,ll> factors;
    ll f = 3, root_n = (ll)(sqrt(n) + 0.5);

    // factor: 2
    while (n % 2 == 0) {
        factors[2]++;
        n /= 2;
    }

    // factor: 3, 5, 7, 11, ...
    while (f <= root_n) {
        if (n % f == 0) {
            factors[f]++;
            n /= f;
        }
        else {
            f += 2;
        }
    }

    if (n != 1) factors[n]++;
    return factors;
}


int main() {
    int n;
    cin >> n;

    auto factors = prime_factorization(n);
    cout << n << ":";
    for (auto& m : factors) {
        ll f = m.first;
        ll n = m.second;
        while (n--) cout << " " << f;
    }
    cout << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=ja
