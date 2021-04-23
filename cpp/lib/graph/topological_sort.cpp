#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


// reference:
//   <https://en.wikipedia.org/wiki/Topological_sorting>
//   <https://www.slideshare.net/hcpc_hokudai/topological-sort-69581002/24>

// 0-based index
VLL topological_sort(const VVLL& G) {
    const ll N = (ll)G.size();
    VLL L(N);  // result of topological sort
    ll k = 0;

    VLL indeg(N, 0);  // indegree
    REP(u,N) for (ll v : G[u]) indeg[v]++;  // count indegree for each vertex

    queue<ll> q;  // set of vertices with 0 indegree
    REP(u,N) if (indeg[u] == 0) q.push(u);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        L[k++] = u;
        for (ll v : G[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }
    return L;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VVLL G(N);
    REP(_,M) {
        ll s, t; cin >> s >> t;
        // s--; t--;
        G[s].push_back(t);
    }

    auto L = topological_sort(G);
    for (ll u : L) {
        cout << u << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=ja
