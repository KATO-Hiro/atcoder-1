#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


// References:
//   <https://ei1333.github.io/luzhiled/snippets/tree/centroid-decomposition.html>
//   <https://tjkendev.github.io/procon-library/cpp/graph/centroid-decomposition.html>
//   <https://atcoder.jp/contests/yahoo-procon2018-final-open/submissions/2376520>

/**
 * @brief 重心分解 (Centroid Decomposition)
 * 
 */
struct CentroidDecomposition {
    int N;
    vector<vector<int>> G;
    vector<int> sz;  // 頂点 u を根とする部分木のサイズ
    vector<bool> centroid;  // 頂点 u が重心として使用されているか
    CentroidDecomposition(int n) : N(n) {
        G.resize(N);
        sz.resize(N);
        centroid.resize(N);
    }

    // 双方向に辺を張る
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // 現時点の部分木のサイズを求める
    int dfs_sz(int u, int p) {
        int s = 1;
        for (int v : G[u]) if (v != p) {
            if (centroid[v]) continue;
            s += dfs_sz(v, u);
        }
        return sz[u] = s;
    }

    // 重心を探索する
    int search_centroid(int u, int p, int cc_sz) {
        for (int v : G[u]) if (v != p) {
            if (centroid[v]) continue;
            if (sz[v] > cc_sz / 2) return search_centroid(v, u, cc_sz);
        }
        return u;
    }

    // 重心分解
    //   - c_root  : 重心の根
    //   - c_graph : 重心から次の重心に有向辺を張ったグラフ
    int build(vector<vector<int>>& c_graph) {
        c_graph.resize(N);
        auto dfs = [&](auto self, int u) -> int {
            int c = search_centroid(u, -1, dfs_sz(u, -1));
            centroid[c] = true;
            for (int v : G[c]) {
                if (centroid[v]) continue;
                c_graph[c].push_back(self(self, v));
            }
            centroid[c] = false;
            return c;
        };
        return dfs(dfs, 0);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    CentroidDecomposition cd(N);
    auto& G = cd.G;
    REP(_,N-1) {
        ll u, v; cin >> u >> v;
        u--; v--;
        cd.add_edge(u, v);
    }

    vector<vector<int>> c_graph;
    int c_root = cd.build(c_graph);

    VVP E(N);
    REP(i,Q) {
        ll u, k; cin >> u >> k;
        u--;
        E[u].push_back(P(k, i));
    }

    VLL ans(Q, 0);

    map<ll,ll> mp_all, mp;                // (重心までの距離, 個数)
    vector<pair<int,ll>> dist_all, dist;  // (頂点, 重心までの距離)
    vector<bool> c_used(N, false);        // 重心として使用中か
    auto dfs = [&](auto self, int c) -> void {
        c_used[c] = true;

        // (1) 頂点 u, v が共に 1 つの部分木に含まれるような組 (u, v)
        for (auto u : c_graph[c]) { self(self, u); }

        // (2) 頂点 u, v が異なる部分木に含まれるような組 (u, v)
        // (3) 重心 c と他の頂点 u との組 (c, u)
        mp_all.clear(); dist_all.clear();
        mp_all[0]++; dist_all.push_back({c, 0});  // 重心 c の分 : (3)
        for (auto u : G[c]) if (!c_used[u]) {

            // 部分木に含まれる全頂点について，重心までの距離を計算
            mp.clear(); dist.clear();
            auto dfs2 = [&](auto self, int u, int p, ll d) -> void {
                mp[d]++; dist.push_back({u, d});
                for (auto v : G[u]) if (v != p && !c_used[v]) {
                    self(self, v, u, d + 1);
                }
            };
            dfs2(dfs2, u, c, 1);

            // 重複分を引いておく : (2)(3) で (1) を数えないようにするため
            for (auto [v, d] : dist) {
                for (auto [k, i] : E[v]) {
                    if (mp.count(k - d)) {
                        ans[i] -= mp[k - d];
                    }
                }
            }

            // マージ
            dist_all.insert(dist_all.end(), dist.begin(), dist.end());
            for (auto [d, n] : mp) { mp_all[d] += n; }
        }
        // (2)(3) の計算の本体
        for (auto [v, d] : dist_all) {
            for (auto [k, i] : E[v]) {
                if (mp_all.count(k - d)) {
                    ans[i] += mp_all[k - d];
                }
            }
        }

        c_used[c] = false;
    };
    dfs(dfs, c_root);

    for (ll a : ans) {
        cout << a << '\n';
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/yahoo-procon2018-final-open/tasks/yahoo_procon2018_final_c
