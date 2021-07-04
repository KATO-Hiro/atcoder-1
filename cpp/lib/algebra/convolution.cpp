#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
using VLL = vector<ll>;
static const ll MOD = 998244353;
// --------------------------------------------------------
#include <atcoder/convolution>
using namespace atcoder;

// References:
//   <https://atcoder.github.io/ac-library/master/document_ja/convolution.html>


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VLL A(N); REP(i,N) cin >> A[i];
    VLL B(M); REP(i,M) cin >> B[i];

    auto C = convolution<MOD>(A, B);
    cout_line(C, 0, SZ(C));

    return 0;
}
// Verify: https://atcoder.jp/contests/practice2/tasks/practice2_f
