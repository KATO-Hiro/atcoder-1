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
    vector<tuple<ll,ll,ll>> E(M);
    REP(i,M) {
        ll s, t, w; cin >> s >> t >> w;
        // s--; t--;
        E[i] = {w, s, t};
    }
    SORT(E);

    dsu uf(N);
    ll ans = 0;
    for (auto& [w, s, t] : E) {
        if (uf.same(s, t)) continue;
        uf.merge(s, t);
        ans += w;
    }
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=ja
