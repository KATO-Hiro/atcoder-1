#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


vector<bool> is_prime_numbers(ll n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    ll root_n = (ll)(sqrt(n) + 0.5);
    for (int i = 4; i <= n; i += 2) is_prime[i] = false;
    for (int i = 3; i <= root_n; i += 2) {
        for (int j = 2 * i; j <= n; j += i) {
            is_prime[j] = false;
        }
    }
    return is_prime;
}


// Verify: https://onlinejudge.u-aizu.ac.jp/challenges/search/categories/0053
int main() {
    int MAX_V = 2e+5;
    auto is_prime = is_prime_numbers(MAX_V);

    int MAX_N = 10000;
    vector<ll> s(MAX_N + 1, 0);
    int i, p = 1;
    for (i = 1; i <= MAX_N; i++) {
        while (true) {
            p++;
            if (is_prime[p]) {
                s[i] = s[i - 1] + p;
                break;
            }
        }
    }
    
    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;
        cout << s[n] << endl;
    }

    return 0;
}