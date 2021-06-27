#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
static const ll MOD = 1000000007;
// --------------------------------------------------------

// when p is prime number, 
//   a^b^c = modpow(a,modpow(b,c,p-1),p)  (mod p)
//
// a^{p-1} = 1 (mod p)  # Fermat's little theorem
// a^b^c = a^{q(p-1) + r}
//       = (a^{p-1})^q + a^r
//       = a^r
//       = a^{modpow(b,c,p-1)}  Q.E.D.

ll pow_mod(ll x, ll n, ll mod) {
    ll res = 1;
    if (n > 0) {
        res = pow_mod(x, n / 2, mod);
        if (n % 2 == 0) {
            res = (res * res) % mod;
        } else {
            res = (((res * res) % mod) * x) % mod;
        }
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll Q; cin >> Q;
    while (Q--) {
        ll a, b, c; cin >> a >> b >> c;
        ll ans = pow_mod(a, pow_mod(b, c, MOD-1), MOD);
        cout << ans << '\n';
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1712
