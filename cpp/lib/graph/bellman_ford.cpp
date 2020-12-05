#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
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

// 0-based index
bool bellman_ford(VVE& G, VLL& dist, int s) {
    const int N = (int)G.size();
    assert(N == (int)dist.size());
    assert(0 <= s && s < N);

    dist[s] = 0;
    int v; ll c;
    REP(i, N) REP(u, N) {
        if (dist[u] == INF) continue;
        for (auto cv : G[u]) {
            tie(c, v) = cv;
            if (chmin(dist[v], dist[u] + c)) {
                if (i == N - 1) return true;
            }
        }
    }
    return false;
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
    bool exist_negative_cycle = bellman_ford(G, dist, r);
    if (exist_negative_cycle) {
        cout << "NEGATIVE CYCLE" << '\n';
    } else {
        REP(i, N) {
            if (dist[i] == INF) {
                cout << "INF" << '\n';
            } else {
                cout << dist[i] << '\n';
            }
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B
