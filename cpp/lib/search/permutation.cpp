#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
using VI = vector<int>;
// --------------------------------------------------------


// Verify: https://atcoder.jp/contests/abc150/tasks/abc150_c
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N; cin >> N;
    VI P(N); REP(i,N) cin >> P[i];
    VI Q(N); REP(i,N) cin >> Q[i];

    VI R(N); iota(ALL(R), 1);
    int i = 1;
    int a = 1, b = 1;
    do {
        if (equal(ALL(P), ALL(R))) a = i;
        if (equal(ALL(Q), ALL(R))) b = i;
        i++;
    } while (next_permutation(ALL(R)));

    int ans = abs(a - b);
    cout << ans << '\n';

    return 0;
}
