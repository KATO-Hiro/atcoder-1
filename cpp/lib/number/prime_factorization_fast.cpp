#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define MAX(c) *max_element(ALL(c))
using VLL = vector<ll>;
// --------------------------------------------------------


// 高速素因数分解
//   D[x] := x を割り切る最小の素数 (x が素数の場合は D[x] == x)
//   e.g.) D[4] = D[6] = 2, D[35] = 5
VLL prime_factorization_fast(ll n) {
    VLL D(n+1); iota(ALL(D),0);
    ll root = floorl(sqrtl(n) + 0.5);
    for (ll j = 2*2; j <= n; j += 2) D[j] = 2; 
    for (ll i = 3; i <= root; i += 2) if (D[i] == i) {
        for (ll j = 2*i; j <= n; j += i) if (D[j] == j) D[j] = i;
    }
    return D;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL A(N); REP(i,N) cin >> A[i];

    ll MAX_A = MAX(A);
    auto D = prime_factorization_fast(MAX_A);

    unordered_map<ll,ll> cnt;
    for (ll a : A) {
        while (a != 1) {
            ll f = D[a];
            cnt[f]++;
            while (a % f == 0) { a /= f; }
        }
    }

    bool pairwise = true;
    bool setwise = true;
    for (auto& [_, n] : cnt) {
        if (1 < n) pairwise = false;
        if (n == N) setwise = false;
    }
    string ans;
    if (pairwise) {
        ans = "pairwise coprime";
    } else if (setwise) {
        ans = "setwise coprime";
    } else {
        ans = "not coprime";
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc177/tasks/abc177_e
