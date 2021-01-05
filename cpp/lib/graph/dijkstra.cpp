#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

using E = pair<ll,ll>;  // (cost, to)
using VE = vector<E>;
using VVE = vector<VE>;

// 0-based/1-based index
void dijkstra(VVE& G, VLL& dist, ll s) {
    assert((ll)G.size() == (ll)dist.size());
    assert(0 <= s && s < (ll)G.size());

    dist[s] = 0;
    priority_queue<E, VE, greater<E>> pq;
    pq.push(E(dist[s], s));
    ll u, v, c, min_dist;
    while (!pq.empty()) {
        tie(min_dist, u) = pq.top(); pq.pop();
        if (dist[u] < min_dist) continue;

        for (auto& cv: G[u]) {
            tie(c, v) = cv;
            if (chmin(dist[v], dist[u] + c)) {
                pq.push(E(dist[v], v));
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, M, r; cin >> N >> M >> r;
    VVE G(N);
    ll s, t, d;
    REP(_, M) {
        cin >> s >> t >> d;
        G[s].push_back(E(d, t));
    }

    VLL dist(N, INF);
    dijkstra(G, dist, r);

    REP(i,N) {
        if (dist[i] == INF) {
            cout << "INF" << '\n';
        } else {
            cout << dist[i] << '\n';
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
