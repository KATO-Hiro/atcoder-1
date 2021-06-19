#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

// References:
//   <https://en.wikipedia.org/wiki/K_shortest_path_routing>
//   <http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.30.3705&rep=rep1&type=pdf>


// Finding the k shortest path (walk) from s to t
// This is not "simple" version (vertex can be repeated)
//   - assume non-negative weights
//   - the results can be less than k
//   - O(M + kN log N)
VLL k_shortest_path(const VVP& G, ll k, ll s, ll t) {
    const ll N = SZ(G);
    VVLL dist(N);
    priority_queue<P,VP,greater<P>> pq; pq.push(P(0,s));
    while (!pq.empty()) {
        auto [min_dist, u] = pq.top(); pq.pop();
        if (SZ(dist[u]) >= k) continue;
        dist[u].push_back(min_dist);
        for (auto [v, c] : G[u]) {
            pq.push(P(min_dist + c, v));
        }
    }
    return dist[t];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M, K; cin >> N >> M >> K;
    VVP G(N);
    REP(_,M) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back(P(b, c));
    }

    VLL dist = k_shortest_path(G, K, 0, N-1);

    assert(SZ(dist) == K);
    cout_line(dist, 0, K);

    return 0;
}
// verify: https://cses.fi/problemset/task/1196
