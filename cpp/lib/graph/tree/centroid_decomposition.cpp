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
using VLL = vector<ll>;
using VB = vector<bool>;
// --------------------------------------------------------


// References:
//   <https://ei1333.github.io/luzhiled/snippets/tree/centroid-decomposition.html>
//   <https://tjkendev.github.io/procon-library/cpp/graph/centroid-decomposition.html>
//   <https://atcoder.jp/contests/yahoo-procon2018-final-open/submissions/2376520>
//   <https://usaco.guide/problems/cses-2080-fixed-length-paths-i/solution>

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

    auto enumerate = [&](const VLL& cnt, const VP& dist, ll c) -> void {
        for (auto [v, d] : dist) {
            for (auto [k, i] : E[v]) {
                if (0 <= k-d) {
                    ans[i] += cnt[k-d] * c;
                }
            }
        }
    };

    VLL cnt_all(N,0), cnt(N,0);  // 重心までの深さが d である頂点の個数
    VP dist_all, dist;           // (頂点, 重心までの深さ)
    VB c_used(N, false);         // 重心として使用中か
    auto dfs = [&](auto self, int c) -> void {
        c_used[c] = true;

        // (1) 頂点 u, v が共に 1 つの部分木に含まれるような組 (u, v)
        for (auto u : c_graph[c]) { self(self, u); }

        // (2) 頂点 u, v が異なる部分木に含まれるような組 (u, v)
        // (3) 重心 c と他の頂点 u との組 (c, u)
        int max_depth_all = 0;
        cnt_all[0]++; dist_all.push_back({c, 0});  // 重心 c の分 : (3)
        for (auto u : G[c]) if (!c_used[u]) {

            // 部分木に含まれる全頂点について，重心までの距離を計算
            int max_depth = 0;
            auto dfs2 = [&](auto self, int u, int p, int d) -> void {
                cnt[d]++; dist.push_back({u, d}); chmax(max_depth, d);
                for (auto v : G[u]) if (v != p && !c_used[v]) {
                    self(self, v, u, d + 1);
                }
            };
            dfs2(dfs2, u, c, 1);
            chmax(max_depth_all, max_depth);

            // 重複分を引いておく : (2)(3) で (1) を数えないようにするため
            enumerate(cnt, dist, -1);

            // マージ
            dist_all.insert(dist_all.end(), dist.begin(), dist.end());
            for (int d = 0; d <= max_depth; d++) { cnt_all[d] += cnt[d]; }

            // 初期化
            dist.clear();
            fill(cnt.begin(), cnt.begin() + max_depth + 1, 0);
        }
        // (2)(3) の計算の本体
        enumerate(cnt_all, dist_all, 1);

        // 初期化
        dist_all.clear();
        fill(cnt_all.begin(), cnt_all.begin() + max_depth_all + 1, 0);

        c_used[c] = false;
    };
    dfs(dfs, c_root);

    for (ll a : ans) {
        cout << a << '\n';
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/yahoo-procon2018-final-open/tasks/yahoo_procon2018_final_c

// Others:
//   1. 長さ k のパスの数え上げ
//      <https://cses.fi/problemset/result/2405620/>

