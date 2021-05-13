#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VB = vector<bool>;
using VLL = vector<ll>;
// --------------------------------------------------------


VB is_prime_numbers(ll n) {
    VB is_prime(n+1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    ll root = floorl(sqrtl(n) + 0.5);
    for (ll j = 2*2; j <= n; j += 2) is_prime[j] = false;
    for (ll i = 3; i <= root; i += 2) {
        for (ll j = 2*i; j <= n; j += i) is_prime[j] = false;
    }
    return is_prime;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    static const ll MAX_V = 200000;
    static const ll MAX_N = 10000;

    auto is_prime = is_prime_numbers(MAX_V);
    VLL s(MAX_N+1, 0);

    ll p = 1;
    FOR(i,1,MAX_N+1) {
        s[i] += s[i-1];
        while (!is_prime[p]) p++;
        s[i] += p++;
    }

    while (true) {
        ll n; cin >> n;
        if (n == 0) break;
        cout << s[n] << '\n';
    }

    return 0;
}
// Verify: https://onlinejudge.u-aizu.ac.jp/challenges/search/categories/0053
