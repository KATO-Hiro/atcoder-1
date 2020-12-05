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

using E = pair<ll,int>;  // (cost, to)
using VE = vector<E>;
using VVE = vector<VE>;

// 0-based/1-based index
void dijkstra(VVE& G, VLL& dist, int s) {
    assert((int)G.size() == (int)dist.size());
    assert(0 <= s && s < (int)G.size());

    dist[s] = 0;
    priority_queue<E, VE, greater<E>> pq;
    pq.push(E(dist[s], s));
    int u, v; ll c, min_dist;
    while (!pq.empty()) {
        tie(min_dist, u) = pq.top(); pq.pop();
        if (dist[u] < min_dist) continue;

        for (auto cv: G[u]) {
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

    int N, M, r; cin >> N >> M >> r;
    VVE G(N);
    int s, t; ll d;
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


/*
// Verify: https://atcoder.jp/contests/abc012/tasks/abc012_4
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
*/
