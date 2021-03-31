#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
// --------------------------------------------------------


// 最長増加部分列 (LIS: Longest Increasing Subsequence)
ll lis(const VLL& A) {
    const ll N = SZ(A);
    VLL L = {A[0]};
    FOR(i,1,N) {
        if (L.back() < A[i]) {
            L.push_back(A[i]);
        } else {
            *lower_bound(ALL(L), A[i]) = A[i];
        }
    }
    return SZ(L);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N; cin >> N;
    VLL A(N); REP(i,N) cin >> A[i];

    ll ans = lis(A);
    cout << ans << endl;

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D&lang=ja
