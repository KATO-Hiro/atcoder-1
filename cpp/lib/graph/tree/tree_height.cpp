#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((int)(c).size())
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


/** NOTE: 本実装は O(N^2) (スターグラフの場合)
 *        全方位木 DP によって O(N) で計算可能 **/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVP G(N);
    REP(_,N-1) {
        ll s, t, w; cin >> s >> t >> w;
        // s--; t--;
        G[s].push_back(P(t, w));
        G[t].push_back(P(s, w));
    }

    // dp[u][i] := 頂点 u を根とした場合に頂点 u と隣接する i 番目の部分木の高さ
    VVLL dp(N);
    REP(u,N) dp[u] = VLL(SZ(G[u]), -1);
    auto dfs = [&](auto self, ll u, ll i) -> ll {
        if (dp[u][i] >= 0) return dp[u][i];
        ll res = 0;
        auto [v, w] = G[u][i];
        REP(j,SZ(G[v])) if (G[v][j].first != u) {
            chmax(res, self(self, v, j));
        }
        return dp[u][i] = w + res;
    };

    REP(u,N) {
        ll ans = 0;
        REP(i,SZ(G[u])) chmax(ans, dfs(dfs, u, i));
        cout << ans << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B&lang=ja
