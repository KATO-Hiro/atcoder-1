#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


map<ll,ll> prime_factorization(ll n) {
    map<ll,ll> factors;
    ll f = 3, root = floorl(sqrtl(n) + 0.5);

    // factor: 2
    while (n % 2 == 0) { factors[2]++; n /= 2; }

    // factor: 3, 5, 7, 11, ...
    while (f <= root) {
        while (n % f == 0) { factors[f]++; n /= f; }
        f += 2;
    }

    if (n != 1) factors[n]++;
    return factors;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;

    auto factors = prime_factorization(N);

    cout << N << ":";
    for (auto [f, n] : factors) {
        while (n--) cout << " " << f;
    }
    cout << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=ja
