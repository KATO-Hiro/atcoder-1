#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

using E = pair<ll,int>;
using VE = vector<E>;
using VVE = vector<VE>;

void dijkstra(VVE& G, VLL& dist, int s) {
    dist[s] = 0;
    priority_queue<E, VE, greater<E>> pq;
    pq.push(E(dist[s], s));
    int u, v;
    ll min_dist, dist_u, c, alt;
    while (!pq.empty()) {
        tie(min_dist, u) = pq.top(); pq.pop();
        dist_u = dist[u];
        if (dist_u < min_dist) continue;

        for (auto cv: G[u]) {
            tie(c, v) = cv;
            alt = dist_u + c;
            if (alt < dist[v]) {
                dist[v] = alt;
                pq.push(E(alt, v));
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N, M; cin >> N >> M;
    VVE G(N+1);

    int a, b; ll t;
    REP(_, M) {
        cin >> a >> b >> t;
        G[a].push_back(E(t, b));
        G[b].push_back(E(t, a));
    }

    ll ans = INF;
    FOR(s,1,N+1) {
        VLL dist(N+1, INF);
        dijkstra(G, dist, s);
        ll max_dist = 0;
        FOR(u,1,N+1) chmax(max_dist, dist[u]);
        chmin(ans, max_dist);
    }
    cout << ans << endl;
    return 0;
}
// Verify: https://atcoder.jp/contests/abc012/tasks/abc012_4
