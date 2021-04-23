#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


// 0-based/1-based index
// P := (to, cost)
void dijkstra(const VVP& G, VLL& dist, ll s) {
    assert((ll)G.size() == (ll)dist.size());
    assert(0 <= s && s < (ll)G.size());

    dist[s] = 0;
    priority_queue<P, VP, greater<P>> pq; pq.push(P(dist[s], s));
    while (!pq.empty()) {
        auto [min_dist, u] = pq.top(); pq.pop();
        if (dist[u] < min_dist) continue;
        for (auto& [v, c] : G[u]) {
            if (chmin(dist[v], dist[u] + c)) pq.push(P(dist[v], v));
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, M, r; cin >> N >> M >> r;
    VVP G(N);
    REP(_,M) {
        ll s, t, d; cin >> s >> t >> d;
        // s--; t--;
        G[s].push_back(P(t, d));
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
