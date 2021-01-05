#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
// --------------------------------------------------------
#include <atcoder/dsu>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    vector<tuple<ll,ll,ll>> wst(M);
    ll s, t, w;
    REP(i,M) {
        cin >> s >> t >> w;
        get<0>(wst[i]) = w;
        get<1>(wst[i]) = s;
        get<2>(wst[i]) = t;
    }
    SORT(wst);

    dsu uf(N);
    ll ans = 0;
    for (auto& x : wst) {
        tie(w, s, t) = x;
        if (uf.same(s, t)) continue;
        uf.merge(s, t);
        ans += w;
    }
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A
