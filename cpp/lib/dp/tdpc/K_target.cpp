#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
#define SZ(c) ((ll)(c).size())
using P = pair<ll,ll>;
using VP = vector<P>;
using VLL = vector<ll>;
// --------------------------------------------------------

// NOTE
//   - LIS
//   - 類題: abc038_d

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
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VP X(N);
    REP(i,N) {
        ll x, r; cin >> x >> r;
        X[i] = P(-(x+r), -(x-r));
    }
    SORT(X);
    VLL A(N); REP(i,N) A[i] = -X[i].second;
    ll ans = lis(A);
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_target
