#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------


ll euler_phi(ll n) {
    ll res = n;
    ll root = floor(sqrt(n) + 0.5);
    for (ll f = 2; f <= root; f++) if (n % f == 0) {
        res -= res / f;
        while (n % f == 0) { n /= f; }
    }
    if (n > 1) res -= res / n;
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;

    ll ans = euler_phi(N);
    cout << ans << endl;

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D&lang=ja
