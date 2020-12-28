#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------


// gcd(a, b) を返し， ax + by = gcd(a, b) となるように x, y を書き換える
// `1 <= b` を想定

/**
 * @brief `ax + by = gcd(a, b)` を満たす整数解 x, y を求めて gcd(a, b) を返す．
 * 
 * @param a 整数
 * @param b 1以上の整数
 * @param x 整数解 (参照)
 * @param y 整数解 (参照)
 * @return ll gcd(a, b)
 */
ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (b > 0) {
        ll g = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return g;
    } else {
        x = 1; y = 0;
        return a;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll a, b; cin >> a >> b;

    ll x, y;
    // ll g = extgcd(a, b, x, y);
    extgcd(a, b, x, y);
    cout << x << " " << y << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_E&lang=ja
