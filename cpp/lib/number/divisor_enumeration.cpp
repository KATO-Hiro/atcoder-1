#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


vector<ll> divisor_enumeration(ll n) {
    vector<ll> divisor_l, divisor_r;
    ll e, root_n = (ll)(sqrt(n) + 0.5);
    for (int d = 1; d <= root_n; d++) {
        if (n % d == 0) {
            divisor_l.push_back(d);
            e = n / d;
            if (e != d) divisor_r.push_back(e);
        }
    }
    reverse(divisor_r.begin(), divisor_r.end());
    divisor_l.insert(divisor_l.end(), divisor_r.begin(), divisor_r.end());
    return divisor_l;
}


int main() {
    ll N;
    cin >> N;

    auto F = [](ll A, ll B) -> int {
        return max(to_string(A).size(), to_string(B).size());
    };

    vector<ll> divisors = divisor_enumeration(N);
    int ans = 1 << 30;
    for (ll d: divisors) {
        ans = min(ans, F(d, N / d));
    }
    cout << ans << endl;
    return 0;
}


/*
https://atcoder.jp/contests/abc057/tasks/abc057_c

input 3
-------
9876543210

output 3
--------
6
*/