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

// 1点更新・区間最大・二分探索
using S = ll;
S op(S a, S b) { return max(a, b); }
S e() { return 0; }
S target;
bool f(S v) { return v < target; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    VLL H(N); REP(i,N) cin >> H[i];
    segtree<S, op, e> seg(H);

    VLL ans(Q,0);
    REP(i,Q) {
        ll x; cin >> x;

        // 下記を両方満たす r をセグ木上の二分探索で求める : O(log N)
        //   - max(a[0], ... , a[r-1]) <  target
        //   - max(a[0], ... , a[r])   >= target
        //   <https://atcoder.github.io/ac-library/master/document_ja/segtree.html>
        target = x;
        ll r = seg.max_right<f>(0);
        if (r < N) {
            ans[i] = r + 1;
            seg.set(r, seg.get(r) - x);
        }
    }
    cout_line(ans,0,Q);

    return 0;
}
// Verify: https://cses.fi/problemset/task/1143
