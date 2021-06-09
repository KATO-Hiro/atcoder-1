#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
using VLL = vector<ll>;
// --------------------------------------------------------

// Referenses:
//   <https://drken1215.hatenablog.com/entry/2020/10/01/031200>

// NOTE: 公差 = 1 の例
//   A = {0, 0, 1, 2, 3, 4, 5, 0, 0} を作りたい
//   A = {0, 0, 1, 0, 0, 0, 0, -6, 5} として累積和を 2 回やれば OK
//   A = {0, 0, 1, 1, 1, 1, 1, -5, 0}
//   A = {0, 0, 1, 2, 3, 4, 5, 0, 0}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    VLL A(N+2,0);
    while (Q--) {
        ll l, k; cin >> l >> k;
        l--;
        A[l    ] += 1;
        A[l+k  ] -= k + 1;
        A[l+k+1] += k;
    }
    FOR(i,1,N) A[i] += A[i-1];
    FOR(i,1,N) A[i] += A[i-1];
    cout_line(A,0,N);

    return 0;
}
// verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3165
