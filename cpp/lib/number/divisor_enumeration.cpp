#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------


// 約数列挙 : O(√N)
vector<ll> divisor_enumeration(ll N) {
    vector<ll> L, R;
    ll root = floorl(sqrtl(N) + 0.5);
    for (ll d1 = 1; d1 <= root; d1++) if (N % d1 == 0) {
        ll d2 = N / d1;
        L.push_back(d1);
        if (d1 != d2) R.push_back(d2);
    }
    // 昇順ソート
    reverse(R.begin(), R.end());
    L.insert(L.end(), R.begin(), R.end());
    return L;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll a, b, c; cin >> a >> b >> c;

    auto divisors = divisor_enumeration(c);

    ll ans = 0;
    for (ll d: divisors) {
        if (a <= d && d <= b) ans++;
    }
    cout << ans << endl;

    return 0;
}
// verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_3_D&lang=ja
