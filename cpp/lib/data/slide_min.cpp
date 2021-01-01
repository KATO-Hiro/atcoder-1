#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, K; cin >> N >> K;
    VLL A(N); REP(i,N) cin >> A[i];

    VLL B;
    deque<ll> d;
    REP(i,N) {
        while (!d.empty() && A[d.back()] >= A[i]) d.pop_back();
        d.push_back(i);
        if (0 <= i - K + 1) {
            B.push_back(A[d.front()]);
            if (d.front() == i - K + 1) d.pop_front();
        }
    }
    REP(i,SZ(B)) {
        if (i) cout << " ";
        cout << B[i];
    }
    cout << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D&lang=ja
