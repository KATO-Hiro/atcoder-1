#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
// --------------------------------------------------------


/**
 * @brief LCA (Lowest Common Ancestor): 最小共通祖先
 *        (ダブリングによる実装)
 *        - 前計算: O(NlogN)
 *        - クエリ: O(logN)
 * 
 */
struct LCA {
    int N, root, K;  // 頂点数，根，二進表記の桁数（ダブリング用）
    vector<vector<int>> G;
    vector<vector<int>> parent;  // parent[k][u]: 頂点 u から 2^k 回親を辿って到達する頂点 (根を越えたら -1)
    vector<int> depth;  // depth[u] := 頂点 u の根からの深さ

    LCA(int n, int r = 0) : N(n), root(r) {
        assert(0 <= root && root < N);
        K = 1; while ((1<<K) <= N) { K++; }
        G.resize(N);
        parent.resize(K, vector<int>(N));
        depth.resize(N);
    }

    // 双方向に辺を張る
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void build() {
        // 初期化
        auto dfs = [&](auto self, int u, int p, int d) -> void {
            parent[0][u] = p;
            depth[u] = d;
            for (int v : G[u]) if (v != p) {
                self(self, v, u, d+1);
            }
        };
        dfs(dfs, root, -1, 0);

        // ダブリング
        for (int k = 1; k < K; k++) {
            for (int u = 0; u < N; u++) {
                if (parent[k-1][u] < 0) {
                    parent[k][u] = -1;
                } else {
                    parent[k][u] = parent[k-1][parent[k-1][u]];
                }
            }
        }
    }

    // 頂点 u から深さ d だけ親を辿る (level-ancestor)
    // 辿った先が木上にあることを想定している
    //   - d <= depth[u]
    int la(int u, int d) {
        assert(0 <= u && u < N);
        for (int k = K-1; 0 <= k; k--) if (BIT(d, k)) {
            u = parent[k][u];
        }
        return u;
    }

    // 頂点 u, v の LCA
    int query(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        if (depth[u] < depth[v]) swap(u, v);
        // depth[u] >= depth[v]
        u = la(u, depth[u] - depth[v]);  // (u, v) の深さを揃える
        if (u == v) return u;
        for (int k = K-1; 0 <= k; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    // (u, v) パス間の辺数
    int distance(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return depth[u] + depth[v] - 2*depth[query(u, v)];
    }

    // 頂点 w が (u, v) パス上に存在するか
    bool on_path(int u, int v, int w) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        assert(0 <= w && w < N);
        return distance(u, w) + distance(w, v) == distance(u, v);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    LCA lca(N, 0);
    // REP(_,N-1) {
    //     ll u, v; cin >> u >> v;
    //     u--; v--;
    //     lca.add_edge(u, v);
    // }
    REP(u,N) {
        ll k; cin >> k;
        REP(_,k) {
            ll c; cin >> c;
            lca.add_edge(u, c);
        }
    }
    lca.build();

    ll Q; cin >> Q;
    while (Q--) {
        ll u, v; cin >> u >> v;
        // u--; v--;
        cout << lca.query(u, v) << '\n';
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
