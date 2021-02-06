#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
ll llceil(ll a, ll b) { return (a + b - 1) / b; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define MIN(c) *min_element(ALL(c))
#define MAX(c) *max_element(ALL(c))
#define SUM(c) accumulate(ALL(c), 0)
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) ((b>>i) & 1)
#define PCNT(b) __builtin_popcountll(b)
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << #x << " = " << (x) << '\n';
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VVVLL = vector<VVLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VVVB = vector<VVB>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


VLL topological_sort(VVP& G) {
    const ll N = (ll)G.size();
    VLL L(N);  // result of topological sort
    ll k = 0;

    VLL indeg(N, 0);  // indegree
    REP(u, N) for (auto [c, v] : G[u]) indeg[v]++;  // count indegree for each vertex

    queue<ll> q;  // set of vertices with 0 indegree
    REP(u, N) if (indeg[u] == 0) q.push(u);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        L[k++] = u;
        for (auto [c, v] : G[u]) {
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
    VVLL GG(N,VLL(N,INF));
    REP(_,M) {
        ll s, t, d; cin >> s >> t >> d;
        s--; t--;
        chmin(GG[s][t], d);
    }

    VLL ans(N,INF);
    VVP G(N);  // cost, to
    REP(i,N) REP(j,N) {
        if (GG[i][j] != INF) {
            if (i == j) {
                chmin(ans[i], GG[i][j]);
            } else {
                G[i].push_back(P(GG[i][j],j));
            }
        }
    }

    REP(s,N) {
        VLL dist(N,INF); dist[s] = 0;
        priority_queue<P, VP, greater<P>> pq;
        pq.push(P(dist[s], s));
        while (!pq.empty()) {
            auto [min_dist, u] = pq.top(); pq.pop();
            if (dist[u] < min_dist) continue;
            for (auto& [c, v] : G[u]) {
                if (v == s) {
                    chmin(ans[s], dist[u] + c);
                } else {
                    if (chmin(dist[v], dist[u] + c)) {
                        pq.push(P(dist[v], v));
                    }
                }
            }
        }
        // VLL indeg(N, 0);  // indegree
        // REP(u, N) for (auto [c, v] : G[u]) indeg[v]++;  // count indegree for each vertex
        // queue<P> q;  // set of vertices with 0 indegree
        // q.push(P(s, 0));
        // while (!q.empty()) {
        //     auto [u, cost] = q.front(); q.pop();
        //     if (dist[u] < cost) continue;
        //     for (auto [c, v] : G[u]) {
        //         indeg[v]--;
        //         if (indeg[v] == 0) {
        //             if (v == s) {
        //                 chmin(ans[s], cost + c);
        //             } else {
        //                 if (chmin(dist[v], cost + c)) {
        //                     q.push(P(v, dist[v]));
        //                 }
        //             }
        //         }
        //     }
        // }
        // if (dist[s] == INF) {
        //     if (ans[s] != INF) {
        //         ans[s] = -1;
        //     } 
        // } else {
        //     chmin(ans[s], dist[s]);
        // }
    }
    REP(i,N) if (ans[i] == INF) ans[i] = -1;
    REP(i,N) COUT(ans[i]);

    return 0;
}
