#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
static const ll MOD = 1000000007;
// --------------------------------------------------------


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

    ll m, n; cin >> m >> n;

    ll ans = pow_mod(m, n, MOD);
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B&lang=ja
