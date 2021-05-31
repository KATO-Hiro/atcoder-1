#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
#define SZ(c) ((ll)(c).size())
#define COUT(c) cout << (c) << '\n'
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点加算・区間総和・二分探索
ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }
ll target;
bool f(ll v) { return v < target; }


VLL compress(VLL& X) {
    const ll N = SZ(X);
    VLL XS(X);  // 圧縮前の座標配列 (圧縮後の座標と1対1対応)

    // 重複削除
    SORT(XS);
    XS.erase(unique(ALL(XS)), XS.end());

    // 圧縮後の座標の割り当て
    REP(i,N) {
        X[i] = lower_bound(ALL(XS), X[i]) - XS.begin();
    }
    return XS;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll Q; cin >> Q;
    VLL T(Q),X(Q); REP(i,Q) cin >> T[i] >> X[i];

    VLL A(Q,0);
    REP(i,Q) if (T[i] == 1) A[i] = X[i];

    VLL ZA = compress(A);
    ll W = SZ(ZA);
    segtree<ll, op, e> seg(W);

    REP(i,Q) {
        if (T[i] == 1) {
            seg.set(A[i], seg.get(A[i]) + 1);
        } else {
            target = X[i];
            ll k = seg.max_right<f>(0);
            seg.set(k, seg.get(k) - 1);
            COUT(ZA[k]);
        }
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/arc033/tasks/arc033_3
