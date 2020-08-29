#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


ll pow(ll x, ll n, ll mod) {
    ll res = 1;
    if (n > 0) {
        res = pow(x, n / 2, mod);
        if (n % 2 == 0) res = (res * res) % mod;
        else res = (((res * res) % mod) * x) % mod;
    }
    return res;
}


int main() {
    const int MOD = 1e+9 + 7;
    int m, n;
    cin >> m >> n;
    ll ans = pow(m, n, MOD);
    cout << ans << endl;
    return 0;
}

/*
https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B

input 2
-------
5 8

output 2
--------
390625

*/