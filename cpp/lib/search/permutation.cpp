#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
using VLL = vector<ll>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N; cin >> N;
    VLL P(N); REP(i,N) cin >> P[i];
    VLL Q(N); REP(i,N) cin >> Q[i];

    VLL R(N); iota(ALL(R), 1);
    ll i = 1;
    ll a = 1, b = 1;
    do {
        if (equal(ALL(P), ALL(R))) a = i;
        if (equal(ALL(Q), ALL(R))) b = i;
        i++;
    } while (next_permutation(ALL(R)));

    ll ans = llabs(a - b);
    cout << ans << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/abc150/tasks/abc150_c
