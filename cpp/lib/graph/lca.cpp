#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (int i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
using VI = vector<int>;
using VVI = vector<VI>;
// --------------------------------------------------------

struct LCA {
    VVI parent;  // parent[k][u]: parent that climbed 2^k times from u (doubling)
    VI depth;  // depth from root
    int N;  // number of vertices
    int K;  // number of digit in binary notation for doubling
    LCA(const VVI& G, int root) { init(G, root); }

    void init(const VVI& G, int root) {
        N = (int)G.size();
        K = 1;
        while ((1 << K) <= N) K++;
        parent = VVI(K, VI(N, 0));
        depth = VI(N);

        // initialize parent[0] and depth
        auto dfs = [&](auto f, int u, int p, int d) -> void {
            parent[0][u] = p;
            depth[u] = d;
            for (int v : G[u]) {
                if (v == p) continue;
                f(f, v, u, d + 1);
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
    int la(int u, int d) {
        RREP(k,K) {
            if (d & (1 << k)) {
                u = parent[k][u];
            }
        }
        return u;
    }

    int query(int u, int v) {
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

    // [TODO] verify
    int distance(int u, int v) {
        return depth[u] + depth[v] - 2*depth[query(u, v)];
    }

    // [TODO] verify
    // whether w is on the path of u and v
    bool on_path(int u, int v, int w) {
        return distance(u, w) + distance(w, v) == distance(u, v);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N; cin >> N;
    VVI G(N);
    REP(u,N) {
        int k; cin >> k;
        REP(_,k) {
            int c; cin >> c;
            G[u].push_back(c);
            G[c].push_back(u);
        }
    }

    LCA lca(G, 0);

    int Q; cin >> Q;
    REP(_,Q) {
        int u, v; cin >> u >> v;
        cout << lca.query(u, v) << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja
