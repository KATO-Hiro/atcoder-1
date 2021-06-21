#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
#define COUT(c) cout << (c) << '\n'
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
// --------------------------------------------------------
#include <atcoder/dsu>
using namespace atcoder;

// References:
//   <https://en.wikipedia.org/wiki/Eulerian_path>
//   <https://kokiymgch.hatenablog.com/entry/2017/12/07/193238>


// オイラー路を構築する (Hierholzer's algorithm)
//   - 全頂点が連結であることを想定 (事前に連結性を確認する必要あり)
//   - O(M)
struct EulerianPath {
    int N;
    bool directed;
    vector<vector<pair<int,int>>> G;  // (to, edge_id)
    vector<int> indeg, outdeg;
    vector<bool> used_edge;
    int k = 0;  // 辺番号用

    EulerianPath(int n, bool directed_) : N(n), directed(directed_) {
        G.resize(N);
        indeg.resize(N,0);
        outdeg.resize(N,0);
    }

    // 頂点 u から頂点 v に辺を張る
    //   [無向グラフ] 双方向に辺が張られる
    //   [有向グラフ] 有向辺が張られる
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        if (directed) {
            G[u].push_back({v, k});
        } else {
            G[u].push_back({v, k});
            G[v].push_back({u, k});
        }
        k++;
    }

    void build() {
        for (int u = 0; u < N; u++) {
            for (auto [v, _] : G[u]) {
                outdeg[u]++; indeg[v]++;
            }
        }
    }

    bool _validate_semi(int& s) {
        if (directed) {
            int v_start = -1, v_end = -1;
            for (int u = 0; u < N; u++) {
                if (indeg[u] == outdeg[u]) continue;
                if (outdeg[u] - indeg[u] == 1) {
                    if (v_start != -1) return false;
                    v_start = u;
                } else if (indeg[u] - outdeg[u] == 1) {
                    if (v_end != -1) return false;
                    v_end = u;
                } else {
                    return false;
                }
            }
            if (v_start == -1 || v_end == -1) return false;
            s = v_start;
        } else {
            vector<int> odd_node;
            for (int u = 0; u < N; u++) {
                if (indeg[u] % 2 == 1) {
                    if (odd_node.size() == 2) return false;
                    odd_node.push_back(u);
                }
            }
            if (odd_node.size() != 2) return false;
            s = odd_node[0];
        }
        return true;
    }

    bool _validate_cycle() {
        if (directed) {
            for (int u = 0; u < N; u++) {
                if (indeg[u] != outdeg[u]) return false;
            }
        } else {
            for (int u = 0; u < N; u++) {
                if (indeg[u] % 2 == 1) return false;
            }
        }
        return true;
    }

    vector<int> _construct_core(int s) {
        vector<vector<pair<int,int>>> g(G);  // 破壊的変更をするためコピー生成
        vector<int> path;
        auto dfs = [&](auto self, int u) -> void {
            while (!g[u].empty()) {
                auto [v, edge_id] = g[u].back(); g[u].pop_back();
                if (!used_edge[edge_id]) {
                    used_edge[edge_id] = true;
                    self(self, v);
                    path.push_back(v);
                }
            }
        };
        used_edge.resize(k, false);
        dfs(dfs, s);
        path.push_back(s);
        reverse(path.begin(), path.end());
        return path;
    }

    // オイラー路を構築する (準オイラーグラフ)
    //   - 全頂点が連結であることを想定
    //   - path = { s, ... , t } (始点 s, 終点 t)
    //   - 下記条件を満たさない場合はサイズ 0 の配列を返す
    //     [無向グラフ]
    //       - 次数が奇数の頂点が 2 つだけ存在
    //     [有向グラフ]
    //       - 始点 s : (out-degree) - (in-degree) = 1
    //       - 終点 t : (in-degree) - (out-degree) = 1
    //       - その他 : (in-degree) = (out-degree)
    vector<int> construct_semi() {
        int s;
        if (!_validate_semi(s)) { return vector<int>(0); }
        return _construct_core(s);
    }

    // オイラー閉路を構築する (オイラーグラフ)
    //   - 全頂点が連結であることを想定
    //   - path = { s, ... , t } (始点 s, 終点 t)
    //   - 下記条件を満たさない場合はサイズ 0 の配列を返す
    //     [無向グラフ]
    //       - 全頂点 : 次数が偶数
    //     [有向グラフ]
    //       - 全頂点 : (in-degree) = (out-degree)
    vector<int> construct_cycle(int s = 0) {
        assert(0 <= s && s < N);
        if (!_validate_cycle()) { return vector<int>(0); }
        return _construct_core(s);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    EulerianPath ep(N, false);
    dsu uf(N);
    vector<ll> n_edge(N,0);  // 各連結成分の "辺の数" (union-find と同期)
    REP(_,M) {
        ll u, v; cin >> u >> v;
        u--; v--;
        ep.add_edge(u, v);

        auto ur = uf.leader(u);
        auto vr = uf.leader(v);
        uf.merge(u, v);
        auto r = uf.leader(u);
        if (r != ur) { n_edge[r] += n_edge[ur]; n_edge[ur] = 0; }
        if (r != vr) { n_edge[r] += n_edge[vr]; n_edge[vr] = 0; }
        n_edge[r]++;
    }

    // 連結性の確認
    //   cses1691 の場合は孤立点を無視する問題設定なので辺の数を確認する
    if (n_edge[uf.leader(0)] != M) { COUT("IMPOSSIBLE"); return 0; }
    // if (SZ(uf.groups()) > 1) { COUT("IMPOSSIBLE"); return 0; }

    ep.build();
    auto path = ep.construct_cycle(0);

    if (SZ(path) == 0) {
        COUT("IMPOSSIBLE");
    } else {
        REP(i,SZ(path)) path[i]++;
        cout_line(path,0,SZ(path));
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1691
