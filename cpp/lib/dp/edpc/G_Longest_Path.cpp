#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define MAX(c) *max_element(ALL(c))
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------

// NOTE
//   - DAG DP
//   - トポロジカルソート

VLL topological_sort(VVLL& G) {
    const ll N = (ll)G.size();
    VLL L(N);  // result of topological sort
    ll k = 0;

    VLL indeg(N, 0);  // indegree
    REP(u, N) for (ll v : G[u]) indeg[v]++;  // count indegree for each vertex

    queue<ll> q;  // set of vertices with 0 indegree
    REP(u, N) if (indeg[u] == 0) q.push(u);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        L[k++] = u;
        for (ll v : G[u]) {
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

    ll N, M; cin >> N >> M;
    VVLL G(N);
    REP(_,M) {
        ll x, y; cin >> x >> y;
        x--; y--;
        G[x].push_back(y);
    }

    auto L = topological_sort(G);
 
    VLL dp(N,0);
    for (ll u : L) {
        for (ll v : G[u]) {
            chmax(dp[v], dp[u] + 1);
        }
    }
    ll ans = MAX(dp);
    cout << ans << '\n';

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_g
