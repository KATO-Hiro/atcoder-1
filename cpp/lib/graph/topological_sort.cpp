#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VI = vector<int>;
using VVI = vector<VI>;
// --------------------------------------------------------


// reference:
//   <https://en.wikipedia.org/wiki/Topological_sorting>
//   <https://www.slideshare.net/hcpc_hokudai/topological-sort-69581002/24>

VI topological_sort(VVI& G) {
    const int N = (int)G.size();
    VI indeg(N,0);  // indegree
    queue<int> q;  // set of vertices with 0 indegree
    VI L;  // result of topological sort

    REP(u,N) {
        for (int v : G[u]) {
            indeg[v]++;
        }
    }

    REP(u,N) {
        if (indeg[u] == 0) {
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        L.push_back(u);
        for (int v : G[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    return L;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N, M; cin >> N >> M;
    VVI G(N);
    REP(_,M) {
        int s, t; cin >> s >> t;
        G[s].push_back(t);
    }

    auto L = topological_sort(G);
    for (int u : L) {
        cout << u << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=ja
