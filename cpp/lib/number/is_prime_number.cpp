#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


bool is_prime_number(ll n) {
    if (n == 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    ll f = 3, root_n = (ll)(sqrt(n) + 0.5);
    while (f <= root_n) {
        if (n % f == 0) return false;
        f += 2;
    }
    return true;
}


int main() {
    int n, a, ans = 0;
    cin >> n;
    rep(i, n) {
        cin >> a;
        if (is_prime_number(a)) ans++;
    }
    cout << ans << endl;
    return 0;
}


/*
https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C

input 1
-------
6
2
3
4
5
6
7

output 1
--------
4
*/