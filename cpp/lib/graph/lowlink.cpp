#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (int i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
using P = pair<int,int>;
using VI = vector<int>;
using VVI = vector<VI>;
using VB = vector<bool>;
// --------------------------------------------------------


// References:
//   <https://www.npca.jp/works/magazine/2014_1/>
//   <https://algo-logic.info/articulation-points/>

struct LowLink {
    int N;  // number of vertices
    int r;  // root of tree
    VI par;  // parent
    VI ord;  // visit order
    VI low;  // lowlink
    set<P> bridge;  // set of bridge
    set<int> articulation;  // set of articulation point
    LowLink(const VVI& G, const int root=0) { r=root; init(G); }

    void init(const VVI& G) {
        N = (int)G.size();
        par = VI(N);
        ord = VI(N);
        low = VI(N);

        // calc ord/lowlink
        int k = 0;
        VB used(N, false);
        auto dfs = [&](auto f, int u, int p) -> void {
            par[u] = p;
            used[u] = true;
            ord[u] = low[u] = k++;
            bool is_art = false;  // whether is articulation point
            int n_root_child = 0;
            for (int v : G[u]) {
                if (!used[v]) {
                    if (p == -1) n_root_child++;
                    f(f, v, u);  // dfs
                    low[u] = min(low[u], low[v]);
                    if (ord[u] < low[v]) bridge.insert(P(min(u,v), max(u,v)));
                    if (p != -1 && ord[u] <= low[v]) is_art = true;
                } else if (v != p) {  // backward edge
                    low[u] = min(low[u], ord[v]);
                }
            }
            if (p == -1 && n_root_child > 1) is_art = true;
            if (is_art) articulation.insert(u);
        };
        dfs(dfs, r, -1);
    }

    bool is_bridge(int u, int v) {
        if (u > v) swap(u, v);  // u < v
        return bridge.count(P(u, v)) == 1;
    }

    bool is_articulation(int u) {
        return articulation.count(u) == 1;
    }

};

/*
// Verify: Articulation Point
//   <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=ja>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N, M; cin >> N >> M;
    VVI G(N);
    REP(_,M) {
        int s, t; cin >> s >> t;
        G[s].push_back(t);
        G[t].push_back(s);
    }

    LowLink lowlink(G);

    // REP(u,N) {
    //     if (lowlink.is_articulation(u)) {
    //         cout << u << '\n';
    //     }
    // }

    auto& articulation = lowlink.articulation;
    auto it = articulation.begin();
    while (it != articulation.end()) {
        cout << *it++ << '\n';
    }

    return 0;
}
*/

// Verify: Bridge
//   <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N, M; cin >> N >> M;
    VVI G(N);
    REP(_,M) {
        int s, t; cin >> s >> t;
        G[s].push_back(t);
        G[t].push_back(s);
    }

    LowLink lowlink(G);

    // REP(u,N-1) FOR(v,u+1,N) {
    //     if (lowlink.is_bridge(u, v)) {
    //         cout << u << " " << v << '\n';
    //     }
    // }

    auto& bridge = lowlink.bridge;
    auto it = bridge.begin();
    while (it != bridge.end()) {
        auto p = *it++;
        cout << p.first << " " << p.second << '\n';
    }

    return 0;
}
