#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------

// LCA (Lowest Common Ancestor): 最小共通祖先
// - ダブリングによる実装
struct LCA {
    VVLL parent;  // parent[k][u]: parent that climbed 2^k times from u (doubling)
    VLL depth;  // depth from root
    ll N;  // number of vertices
    ll K;  // number of digit in binary notation for doubling
    LCA(const VVLL& G, ll root) { init(G, root); }

    void init(const VVLL& G, ll root) {
        N = (ll)G.size();
        K = 1;
        while ((1LL << K) <= N) K++;
        parent = VVLL(K, VLL(N, 0));
        depth = VLL(N);

        // initialize parent[0] and depth
        auto dfs = [&](auto self, ll u, ll p, ll d) -> void {
            parent[0][u] = p;
            depth[u] = d;
            for (ll v : G[u]) {
                if (v == p) continue;
                self(self, v, u, d + 1);
            }
        };
        dfs(dfs, root, -1, 0);

        // initialize parent by doubling
        FOR(k,1,K) REP(u,N) {
            if (parent[k-1][u] < 0) {
                parent[k][u] = -1;
            } else {
                parent[k][u] = parent[k-1][parent[k-1][u]];
            }
        }
    }

    // level-ancestor: ancestor of u with depth d
    ll la(ll u, ll d) {
        RREP(k,K) {
            if (d & (1LL << k)) {
                u = parent[k][u];
            }
        }
        return u;
    }

    // LCA of (u, v)
    ll query(ll u, ll v) {
        if (depth[u] < depth[v]) swap(u, v);
        // now, depth[u] >= depth[v]
        u = la(u, depth[u] - depth[v]);
        if (u == v) return u;
        RREP(k,K) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    // number of edges from u to v
    ll distance(ll u, ll v) {
        return depth[u] + depth[v] - 2*depth[query(u, v)];
    }

    // whether w is on the path of (u, v)
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
    REP(_,Q) {
        ll u, v; cin >> u >> v;
        cout << lca.query(u, v) << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
