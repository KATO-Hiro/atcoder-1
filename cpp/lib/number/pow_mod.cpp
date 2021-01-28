#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


ll pow_mod(ll x, ll n, ll mod) {
    ll res = 1;
    if (n > 0) {
        res = pow_mod(x, n / 2, mod);
        if (n % 2 == 0) res = (res * res) % mod;
        else res = (((res * res) % mod) * x) % mod;
    }
    return res;
}


int main() {
    const ll MOD = 1e+9 + 7;
    ll m, n;
    cin >> m >> n;
    ll ans = pow_mod(m, n, MOD);
    cout << ans << endl;
    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B&lang=ja
