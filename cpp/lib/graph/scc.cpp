#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/scc>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VLL K(N); REP(i,N) cin >> K[i];
    VVLL G(N);
    scc_graph g(N);
    REP(_,M) {
        ll s, t; cin >> s >> t;
        s--; t--;
        G[s].push_back(t);
        g.add_edge(s, t);
    }

    auto scc = g.scc();

    // 強連結成分を一つの頂点に潰したグラフを構築
    ll N_scc = SZ(scc);
    VVLL G_scc(N_scc);
    VLL belong(N);
    REP(us,N_scc) for (auto u : scc[us]) belong[u] = us;
    REP(u,N) for (ll v : G[u]) {
        ll us = belong[u], vs = belong[v];
        if (us < vs) { G_scc[us].push_back(vs); }
        if (us > vs) { G_scc[vs].push_back(us); }
    }

    VLL dp(N_scc,-1);
    auto dfs = [&](auto self, ll us) -> ll {
        if (dp[us] != -1) return dp[us];
        ll res = 0;
        for (auto vs : G_scc[us]) {
            chmax(res, self(self, vs));
        }
        for (auto u : scc[us]) res += K[u];
        return dp[us] = res;
    };

    ll ans = 0;
    REP(us,N_scc) {
        dfs(dfs, us);
        chmax(ans, dp[us]);
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://cses.fi/problemset/task/1686
