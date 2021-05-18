#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

// 区間加算・区間総和
struct S { ll v; ll num; };
struct F { ll x; };
S op(S a, S b) { return S{a.v + b.v, a.num + b.num}; }
S e() { return S{0, 0}; }
S mapping(F f, S a) { return S{a.v + f.x * a.num, a.num}; }
F composition(F f, F g) { return F{f.x + g.x}; }
F id() { return F{0}; }


// References:
//   <https://cp-algorithms.com/graph/hld.html>
//   <https://codeforces.com/blog/entry/53170>
//   <https://ei1333.github.io/luzhiled/snippets/tree/heavy-light-decomposition.html>
//   <https://atcoder.jp/contests/past202010-open/submissions/21473312>
//   <https://math314.hateblo.jp/entry/2014/06/24/220107>
//   <https://qiita.com/Pro_ktmr/items/4e1e051ea0561772afa3>

/**
 * @brief HL 分解 (Heavy Light Decomposition)
 * 
 */
struct HLD {
    int N, root;
    vector<vector<int>> G;
    vector<int> parent;  // 頂点 u の親
    vector<int> depth;  // 頂点 u の深さ
    vector<int> sz;  // 頂点 u を根とする部分木のサイズ (heavy)
    vector<int> in;  // HL 分解時の探索順序 (Euler Tour)
    vector<int> out;  // 後述
    vector<int> head;  // 頂点 u が属する HL 分解後の連結成分の根
    vector<int> rev;  // 探索順序番号から元の頂点番号への逆引き
    int t = 0;  // 探索順序の計算用

    // [ in[u], out[u] )      := 頂点 u を根とする部分木に対応
    // [ in[head[u]], in[u] ] := HL 分解後の連結成分における頂点 u からその head までのパスに対応

    HLD(int n, int r = 0) : N(n), root(r) {
        G.resize(N); parent.resize(N); depth.resize(N); sz.resize(N);
        in.resize(N); out.resize(N); head.resize(N); rev.resize(N);
    }

    // 双方向に辺を張る
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // 各部分木のサイズを求める
    void dfs_sz(int u, int p, int d) {
        parent[u] = p;
        depth[u] = d;
        sz[u] = 1;
        // heavy edge が先頭に来るように維持しながら探索する
        if (G[u].size() && G[u][0] == p) swap(G[u][0], G[u].back());
        for (int& v : G[u]) if (v != p) {  // NOTE: swap のために int& が必要
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[G[u][0]] < sz[v]) swap(G[u][0], v);
        }
    }

    // HL 分解 (Heavy Light Decomposition)
    void dfs_hld(int u, int p) {
        in[u] = t++;
        rev[in[u]] = u;
        for (int v : G[u]) if (v != p) {
            head[v] = (v == G[u][0] ? head[u] : v);  // heavy or light
            dfs_hld(v, u);
        }
        out[u] = t;
    }

    void build() {
        dfs_sz(root, -1, 0);
        dfs_hld(root, -1);
    }

    // 頂点 u から深さ d だけ親を辿る (level-ancestor)
    int la(int u, int d) {
        while (true) {
            int v = head[u];
            if (in[u] - d >= in[v]) return rev[in[u] - d];
            d -= in[u] - in[v] + 1;
            u = parent[v];
        }
    }

    // LCA(u, v)
    int lca(int u, int v) {
        while (true) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
            v = parent[head[v]];
        }
    }

    // (u, v) パス間の辺数
    int distance(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u, v)];
    }

    // 頂点 w が (u, v) パス上に存在するか
    bool on_path(int u, int v, int w) {
        return distance(u, w) + distance(w, v) == distance(u, v);
    }

    // パス [u,v] に対する更新クエリ
    void apply_path(int u, int v, bool edge, function<void(int, int)> func) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        while (true) {
            if (in[u] > in[v]) swap(u, v);  // in[u] <= in[v]  (u が根側)
            if (head[u] == head[v]) break;
            func(in[head[v]], in[v]);
            v = parent[head[v]];
        }
        func(in[u] + edge, in[v]);
    }

    // パス [u,v] に対する取得クエリ
    template <class S, S (*op)(S, S), S (*e)()>
    S prod_path(int u, int v, bool edge, function<S(int, int)> func) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        S Su = e(), Sv = e();
        while (true) {
            if (in[u] > in[v]) { swap(u, v); swap(Su, Sv); }  // in[u] <= in[v]  (u が根側)
            if (head[u] == head[v]) break;
            Sv = op(Sv, func(in[head[v]], in[v]));
            v = parent[head[v]];
        }
        return op(Su, op(Sv, func(in[u] + edge, in[v])));
    }

    // 頂点 u を根とする部分木に対する更新クエリ
    void apply_subtree(int u, bool edge, function<void(int, int)> func) {
        assert(0 <= u && u < N);
        func(in[u] + edge, out[u] - 1);
    }

    // 頂点 u を根とする部分木に対する取得クエリ
    template <class S>
    S prod_subtree(int u, bool edge, function<void(int, int)> func) {
        assert(0 <= u && u < N);
        return func(in[u] + edge, out[u] - 1);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    HLD hld(N);
    REP(_,N-1) {
        ll u, v; cin >> u >> v;
        // u--; v--;
        hld.add_edge(u, v);
    }
    hld.build();
    bool edge = true;

    vector<S> A(N, S{0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll u, v; cin >> u >> v;
            // u--; v--;
            S res = hld.prod_path<S,op,e>(u, v, edge, [&](int a, int b) {
                return seg.prod(a, b+1);
            });
            cout << res.v << '\n';
        } else {
            ll u, x; cin >> u >> x;
            // u--;
            hld.apply_subtree(u, edge, [&](int a, int b) {
                seg.apply(a, b+1, F{x});
            });
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667


/**
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    HLD hld(N);
    REP(u,N) {
        ll k; cin >> k;
        while (k--) {
            ll c; cin >> c;
            hld.add_edge(u, c);
        }
    }
    hld.build();
    bool edge = true;

    vector<S> A(N, S{0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    ll Q; cin >> Q;
    while (Q--) {
        ll q; cin >> q;
        if (q == 0) {
            ll v, w; cin >> v >> w;
            hld.apply_path(0, v, edge, [&](int a, int b) {
                seg.apply(a, b+1, F{w});
            });
        } else {
            ll u; cin >> u;
            S res = hld.prod_path<S,op,e>(0, u, edge, [&](int a, int b) {
                return seg.prod(a, b+1);
            });
            cout << res.v << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_E&lang=ja
**/
