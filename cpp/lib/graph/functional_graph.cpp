#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
// --------------------------------------------------------


struct FunctionalGraph {
    int N, K;
    vector<pair<int,ll>> f;  // 頂点 u から出る有向辺
    vector<vector<pair<int,ll>>> Gr;  // 逆辺グラフ
    vector<int> comp;  // 頂点 u が属する連結成分の番号
    vector<int> root;  // 頂点 u が属する木の根（サイクルに属する頂点は自身が根）
    int cc_id = 0;  // 連携成分の番号用

    // サイクル
    vector<int> cycle_length;  // i 番目の連結成分に含まれるサイクル長
    vector<int> cycle_weight;  // i 番目の連結成分に含まれるサイクル総距離
    vector<int> cycle_dist_e;  // サイクル上の頂点 u における辺数の累積和
    vector<ll> cycle_dist_w;  // サイクル上の頂点 u における距離の累積和

    // 木（複数存在することに注意）
    vector<vector<int>> parent;  // parent[k][u]: 頂点 u から 2^k 回親を辿って到達する頂点 (根を越えたら -1)
    vector<int> depth;  // depth[u] :=  頂点 u の根からの深さ
    vector<ll> dist;  // dist[u] :=  頂点 u の根からの距離 (パス上の重みの総和)

    FunctionalGraph(int n) : N(n) {
        f.resize(N);
        Gr.resize(N);
        comp.resize(N,-1);
        root.resize(N,-1);

        cycle_dist_e.resize(N,0);
        cycle_dist_w.resize(N,0);

        K = 1; while ((1<<K) <= N) { K++; }
        parent.resize(K, vector<int>(N));
        depth.resize(N);
        dist.resize(N,0);
    }

    void add_edge(int u, int v, ll w) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        f[u] = {v, w};
        Gr[v].push_back({u, w});
    }

    // Functional Graph におけるサイクル検出 (Floyd's cycle-finding algorithm)
    // (サイクルに属する頂点の一つ, サイクル長) のペアを返す
    pair<int,int> _cycle_detection(int x) {
        int a = f[x].first;
        int b = f[f[x].first].first;
        while (a != b) {
            a = f[a].first;
            b = f[f[b].first].first;
        }
        b = f[a].first;
        int length = 1;
        while (a != b) {
            b = f[b].first;
            length++;
        }
        return make_pair(a, length);
    }

    void build() {
        // 連結成分分解とサイクル検出
        for (int s = 0; s < N; s++) if (root[s] == -1) {
            // サイクル検出
            auto [x, length] = _cycle_detection(s);
            cycle_length.push_back(length);

            // サイクル上の頂点をチェック
            int r = x;
            for (int i = 0; i < length; i++) {
                root[r] = r; r = f[r].first;
            }

            // 木上の頂点をチェック
            r = x; ll sum_w = 0;
            for (int i = 0; i < length; i++) {
                auto dfs = [&](auto self, int u) -> void {
                    root[u] = r; comp[u] = cc_id;
                    for (auto [v, _] : Gr[u]) if (root[v] == -1) {
                        self(self, v);
                    }
                };
                dfs(dfs, r);
                sum_w += f[r].second;
                r = f[r].first;
                cycle_dist_w[r] = sum_w;
                cycle_dist_e[r] = i + 1;
            }
            cc_id++;
            cycle_weight.push_back(sum_w);
        }

        // 木の初期化
        for (int r = 0; r < N; r++) if (root[r] == r) {
            auto dfs = [&](auto self, int u, int p, int d, ll sum_w) -> void {
                parent[0][u] = p;
                depth[u] = d;
                dist[u] = sum_w;
                for (auto [v, w] : Gr[u]) if (u != v && root[v] == r) {
                    self(self, v, u, d+1, sum_w + w);
                }
            };
            dfs(dfs, r, -1, 0, 0);
        }

        // ダブリング (木に属する頂点のみ対象)
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

    // 連結成分ごとの頂点リストを返す
    vector<vector<int>> groups() {
        vector<vector<int>> g(cc_id);
        for (int u = 0; u < N; u++) {
            g[comp[u]].push_back(u);
        }
        return g;
    }

    // 頂点 u がサイクルに属しているか判定（木の根もサイクルに属するとみなされる）
    bool on_cycle(int u) {
        assert(0 <= u && u < N);
        return (root[u] == u);
    }

    // 頂点 u, v が同じ連結成分に属しているか判定
    bool same_comp(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return (comp[u] == comp[v]);
    }

    // 頂点 u, v が同じ木に属しているか判定
    bool same_tree(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return (root[u] == root[v]);
    }

    // 頂点 u, v が同じサイクルに属しているか判定
    bool same_cycle(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return (same_comp(u, v) && on_cycle(u) && on_cycle(v));
    }

    // 頂点 u から深さ d だけ親を辿る (level-ancestor)
    int la(int u, int d) {
        for (int k = K-1; 0 <= k; k--) if (BIT(d, k)) {
            u = parent[k][u];
        }
        return u;
    }

    // lca(u, v)
    // 同じ木に属することを想定している
    //   - same_tree(u, v) == true
    int lca(int u, int v) {
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

    // (u -> v) パス間の辺数
    // パスが存在しない場合は -1 を返す
    int distance_e(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        if (!same_comp(u, v)) return -1;  // 連結成分が異なる場合は到達不可能

        int res = 0;
        if (same_tree(u, v)) {  // 同じ木に属する
            res = (lca(u, v) == v ? _distance_e_tree(u, v) : -1);
        } else if (on_cycle(u) && on_cycle(v)) {  // 同じサイクルに属する
            res = _distance_e_cycle(u, v);
        } else if (!on_cycle(u) && on_cycle(v)) {  // 木からサイクルへ
            res = _distance_e_tree(u, root[u]) + _distance_e_cycle(root[u], v);
        } else if (on_cycle(u) && !on_cycle(v)) {  // サイクルから木へ
            res = -1;
        } else if (!on_cycle(u) && !on_cycle(v)) {  // 別々の木に属する
            res = -1;
        } else {
            assert(false);
        }
        return res;
    }

    // (u -> v) パス間の距離
    // パスが存在しない場合は -1 を返す
    ll distance_w(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        if (!same_comp(u, v)) return -1;  // 連結成分が異なる場合は到達不可能

        ll res = 0;
        if (same_tree(u, v)) {  // 同じ木に属する
            res = (lca(u, v) == v ? _distance_w_tree(u, v) : -1);
        } else if (on_cycle(u) && on_cycle(v)) {  // 同じサイクルに属する
            res = _distance_w_cycle(u, v);
        } else if (!on_cycle(u) && on_cycle(v)) {  // 木からサイクルへ
            res = _distance_w_tree(u, root[u]) + _distance_w_cycle(root[u], v);
        } else if (on_cycle(u) && !on_cycle(v)) {  // サイクルから木へ
            res = -1;
        } else if (!on_cycle(u) && !on_cycle(v)) {  // 別々の木に属する
            res = -1;
        } else {
            assert(false);
        }
        return res;
    }

    // 木における (u -> v) パス間の辺数
    // パスが存在することを想定している
    //   - same_tree(u, v) == true
    //   - lca(u, v) == v
    int _distance_e_tree(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return depth[u] - depth[v];
    }

    // サイクルにおける (u -> v) パス間の辺数
    // パスが存在することを想定している
    //   - same_cycle(u, v) == true
    int _distance_e_cycle(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        int length = cycle_length[comp[u]];
        return (cycle_dist_e[v] - cycle_dist_e[u] + length) % length;
    }

    // 木における (u -> v) パス間の距離
    // パスが存在することを想定している
    //   - same_tree(u, v) == true
    //   - lca(u, v) == v
    ll _distance_w_tree(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return dist[u] - dist[v];
    }

    // サイクルにおける (u -> v) パス間の距離
    // パスが存在することを想定している
    //   - same_cycle(u, v) == true
    ll _distance_w_cycle(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        ll weight = cycle_weight[comp[u]];
        return (cycle_dist_w[v] - cycle_dist_w[u] + weight) % weight;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    FunctionalGraph fg(N);
    REP(u,N) {
        ll v; cin >> v;
        v--;
        fg.add_edge(u, v, 1);
    }
    fg.build();

    while (Q--) {
        ll a, b; cin >> a >> b;
        a--; b--;
        ll ans = fg.distance_e(a, b);
        cout << ans << '\n';
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1160
