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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, W; cin >> N >> W;
    VLL v(N),w(N); REP(i,N) cin >> v[i] >> w[i];

    ll N1 = N / 2;
    ll N2 = N - N1;
    VP X, Y;  // {(w, v)}
    REP(bit, 1<<N1) {
        ll vv = 0, ww = 0;
        REP(i,N1) if (bit & (1 << i)) { vv += v[i]; ww += w[i]; }
        X.push_back(P(ww, vv));
    }
    REP(bit, 1<<N2) {
        ll vv = 0, ww = 0;
        REP(i,N2) if (bit & (1 << i)) { vv += v[N1+i]; ww += w[N1+i]; }
        Y.push_back(P(ww, vv));
    }

    SORT(X);  // w 昇順ソート
    FOR(i,1,SZ(X)) chmax(X[i].second, X[i-1].second);  // v を単調増加に修正
    VLL Z(SZ(X)); REP(i,SZ(Z)) Z[i] = X[i].first;  // 二分探索用 (w 昇順列)
    ll ans = 0;
    REP(i,SZ(Y)) {
        ll ww = Y[i].first;
        ll vv = Y[i].second;
        auto it = upper_bound(ALL(Z), W - ww);
        if (it == Z.begin()) continue;
        ll j = (it - 1) - Z.begin();
        chmax(ans, X[j].second + vv);
    }
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_H&lang=ja
