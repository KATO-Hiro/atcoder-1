#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


/**
 * @brief 重み付き木の直径を求める
 * 
 * @param G 重み付き木を構成する隣接リスト
 * @return pair<ll, P> : 木の直径と最遠頂点ペア
 */
pair<ll, P> tree_diameter(const VVP& G) {
    ll max_u = -1;
    ll max_d = -INF;
    auto dfs = [&](auto self, ll u, ll p, ll d) -> void {
        if (chmax(max_d, d)) max_u = u;
        for (auto [v, w] : G[u]) if (v != p) {
            self(self, v, u, d + w);
        }
    };
    dfs(dfs, 0, -1, 0);
    ll u1 = max_u;
    dfs(dfs, max_u, -1, 0);
    ll u2 = max_u;
    return make_pair(max_d, P(u1, u2));
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
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=ja
