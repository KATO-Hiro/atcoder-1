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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVP G(N);
    REP(_,N-1) {
        ll s, t, w; cin >> s >> t >> w;
        // s--; t--;
        G[s].push_back(P(t, w));
        G[t].push_back(P(s, w));
    }

    // dp[r][k] := 根とした頂点 r から出る k 番目の辺に関する部分木の高さ
    VVLL dp(N);
    REP(u,N) dp[u] = VLL(SZ(G[u]), -INF);
    auto rec = [&](auto self, ll i, ll j) -> ll {
        if (dp[i][j] >= 0) return dp[i][j];
        auto& [u, w] = G[i][j];
        ll res = 0;
        REP(v, SZ(G[u])) if (G[u][v].first != i) {
            chmax(res, self(self, u, v));
        }
        return dp[i][j] = w + res;
    };

    REP(u,N) {
        ll ans = 0;
        REP(v,SZ(G[u])) chmax(ans, rec(rec, u, v));
        cout << ans << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B&lang=ja
