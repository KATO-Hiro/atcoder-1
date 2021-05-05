#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


/**
 * @brief LCA (Lowest Common Ancestor): 最小共通祖先
 *        (ダブリングによる実装)
 *        - 前計算: O(NlogN)
 *        - クエリ: O(logN)
 * 
 */
struct LCA {
    // parent[k][u]: 頂点 u から 2^k 回親を辿って到達する頂点 (ダブリング)
    //               根を越えたら -1
    VVLL parent;
    VLL depth;  // depth[u] := 頂点 u の根からの深さ
    ll N;  // 頂点数
    ll K;  // 二進表記の桁数 (ダブリング用)
    LCA(const VVLL& G, ll root) {
        N = (ll)G.size();
        assert(0 <= root && root < N);
        K = 1; while ((1LL << K) <= N) K++;
        parent.resize(K, VLL(N));
        depth.resize(N);

        // 初期化
        auto dfs = [&](auto self, ll u, ll p, ll d) -> void {
            parent[0][u] = p;
            depth[u] = d;
            for (ll v : G[u]) if (v != p) {
                self(self, v, u, d + 1);
            }
        };
        dfs(dfs, root, -1, 0);

        // ダブリング
        FOR(k,1,K) REP(u,N) {
            if (parent[k-1][u] < 0) {
                parent[k][u] = -1;
            } else {
                parent[k][u] = parent[k-1][parent[k-1][u]];
            }
        }

    }

    // 頂点 u から深さ d だけ親を辿る (level-ancestor)
    ll la(ll u, ll d) {
        RREP(k,K) if (BIT(d, k)) {
            u = parent[k][u];
        }
        return u;
    }

    // LCA(u, v)
    ll query(ll u, ll v) {
        if (depth[u] < depth[v]) swap(u, v);
        // depth[u] >= depth[v]
        u = la(u, depth[u] - depth[v]);  // (u, v) の深さを揃える
        if (u == v) return u;
        RREP(k,K) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    // (u, v) パス間の辺数
    ll distance(ll u, ll v) {
        return depth[u] + depth[v] - 2*depth[query(u, v)];
    }

    // 頂点 w が (u, v) パス上に存在するか
    bool on_path(ll u, ll v, ll w) {
        return distance(u, w) + distance(w, v) == distance(u, v);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL G(N);
    REP(u,N) {
        ll k; cin >> k;
        REP(_,k) {
            ll c; cin >> c;
            G[u].push_back(c);
            G[c].push_back(u);
        }
    }

    LCA lca(G, 0);

    ll Q; cin >> Q;
    while (Q--) {
        ll u, v; cin >> u >> v;
        cout << lca.query(u, v) << '\n';
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
