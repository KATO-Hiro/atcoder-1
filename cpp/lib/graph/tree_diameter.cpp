#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


/**
 * @brief 重み付き木の直径を求める
 * 
 * @param G 重み付き木を構成する隣接リスト
 * @return pair<ll, P> : 木の直径と最遠頂点ペア
 */
pair<ll, P> tree_diameter(VVP& G) {
    ll N = (ll)G.size();
    auto bfs = [&](ll s) -> P {
        VLL dist(N,INF); dist[s] = 0;
        queue<ll> q; q.push(s);
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (auto& [v, w] : G[u]) {
                if (chmin(dist[v], dist[u] + w)) q.push(v);
            }
        }
        ll max_u = -1;
        ll max_d = -INF;
        REP(u,N) if (chmax(max_d, dist[u])) max_u = u;
        return P(max_u, max_d);
    };
    auto [u, _] = bfs(0);
    auto [v, d] = bfs(u);
    return make_pair(d, P(u, v));
};


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

    auto [d, p] = tree_diameter(G);
    cout << d << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
