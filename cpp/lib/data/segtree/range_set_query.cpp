#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/fenwicktree>
using namespace atcoder;


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

    ll N, Q; cin >> N >> Q;
    VLL X(N); REP(i,N) cin >> X[i];
    vector<tuple<ll,ll,ll>> E(Q);
    REP(i,Q) {
        ll l, r; cin >> l >> r;
        l--; r--;
        E[i] = {r, l, i};
    }
    SORT(E);  // r の昇順にソート

    VLL ZX = compress(X);
    ll M = SZ(ZX);
    fenwick_tree<ll> fw(N);
 
    VLL last(M,-1);  // last[i] := i が最後に出現した位置
    VLL ans(Q);
    ll pos = 0;
    for (auto [r, l, i] : E) {
        while (pos <= r) {
            ll x = X[pos];
            if (last[x] != -1) { fw.add(last[x], -1); }  // 直前の情報を削除
            fw.add(pos, 1);
            last[x] = pos;
            pos++;
        }
        ans[i] = fw.sum(l, r+1);
    }

    REP(i,Q) { cout << ans[i] << '\n'; }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1734
