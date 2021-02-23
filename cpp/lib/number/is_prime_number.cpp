#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


// bool is_prime_number(ll n) {
//     if (n == 1) return false;
//     if (n == 2) return true;
//     if (n % 2 == 0) return false;

//     ll f = 3, root_n = (ll)(sqrt(n) + 0.5);
//     while (f <= root_n) {
//         if (n % f == 0) return false;
//         f += 2;
//     }
//     return true;
// }


bool is_prime_number(ll n) {
    assert(1 <= n);
    if (n == 1) return false;
    if (n == 2) return true;
    if (n == 3) return true;
    if (n % 2 == 0) return false;
    if (n % 3 == 0) return false;

    // 3 より大きい素数は 6k±1 で表される
    ll root = floor(sqrt(n) + 0.5);
    ll f = 6;
    while (f-1 <= root) {
        if (n % (f-1) == 0) return false;
        if (n % (f+1) == 0) return false;
        f += 6;
    }
    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll ans = 0;
    ll Q; cin >> Q;
    while (Q--) {
        ll N; cin >> N;
        if (is_prime_number(N)) ans++;
    }
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C&lang=ja
