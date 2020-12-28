#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------


// `ax + by = gcd(a, b)` を満たす整数解 x, y を求めて gcd(a, b) を返す．
// 制約: 1 <= b
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


// ax ≡ 1 (mod m) を満たす x (0 <= x < m) を返す．
// (mod m における a の逆元 a^-1 を求める)
// 制約: gcd(a, m) = 1, 1 <= m
ll inv_mod(ll a, ll m) {
    assert(1 <= m);
    ll x, y;
    ll g = extgcd(a, m, x, y);
    assert(g == 1);
    return x;
}


// 負数に対応した mod 計算
ll mod(ll x, ll m) {
    return (x % m + m) % m;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll T; cin >> T;
    while (T--) {
        ll N, S, K; cin >> N >> S >> K;

        // S + Kx = Ny
        // Kx ≡ -S (mod N)
        ll g = gcd(K, N);
        if (S % g != 0) {
            cout << -1 << '\n';
            continue;
        }
        N /= g; S /= g; K /= g;
        ll x = inv_mod(K, N);
        ll ans = mod(-S * x, N);
        cout << ans << '\n';
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/abc186/tasks/abc186_e
