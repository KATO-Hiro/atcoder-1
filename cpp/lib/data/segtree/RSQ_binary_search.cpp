#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点加算・区間総和・二分探索
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }
S target;
bool f(S v) { return v < target; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL X(N); REP(i,N) cin >> X[i];

    VLL Y(N,1);
    segtree<S, op, e> seg(Y);

    VLL ans(N,0);
    REP(i,N) {
        ll p; cin >> p;

        // 下記を両方満たす r をセグ木上の二分探索で求める : O(log N)
        //   - sum(a[0], ... , a[r-1]) <  target
        //   - sum(a[0], ... , a[r])   >= target
        //   <https://atcoder.github.io/ac-library/master/document_ja/segtree.html>
        target = p;
        ll r = seg.max_right<f>(0);

        ans[i] = X[r];
        seg.set(r, 0);
    }
    cout_line(ans,0,N);

    return 0;
}
// Verify: https://cses.fi/problemset/task/1143
