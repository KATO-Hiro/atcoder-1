#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N, K; cin >> N >> K;
    ll L, R; cin >> L >> R;
    VLL A(N); REP(i,N) cin >> A[i];

    int N1 = N / 2;
    int N2 = N - N1;

    VVLL X(N1 + 1), Y(N2 + 1);
    REP(bit, 1<<N1) {
        int n = __builtin_popcount(bit);
        ll sum = 0;
        REP(i,N1) if (bit & (1 << i)) sum += A[i];
        X[n].push_back(sum);
    }
    REP(bit, 1<<N2) {
        int n = __builtin_popcount(bit);
        ll sum = 0;
        REP(i,N2) if (bit & (1 << i)) sum += A[N1 + i];
        Y[n].push_back(sum);
    }

    REP(i,N2+1) SORT(Y[i]);  // ソートは右半分だけで十分

    ll ans = 0;
    REP(n1,N1+1) {
        int n2 = K - n1;
        if (n2 < 0 || N2 < n2) continue;
        for (ll sum1 : X[n1]) {
            auto it1 = lower_bound(ALL(Y[n2]), L - sum1);
            auto it2 = upper_bound(ALL(Y[n2]), R - sum1);
            ans += (ll)(it2 - it1);
        }
    }
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_4_B&lang=ja
