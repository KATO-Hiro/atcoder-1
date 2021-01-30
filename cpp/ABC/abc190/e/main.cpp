#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
ll llceil(ll a, ll b) { return (a + b - 1) / b; }
ll llfloor(ll a, ll b) { return a / b; }
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
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << #x << " = " << (x) << '\n';
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;
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
// static const int INF = (1 << 30) - 1;  // 1073741824 - 1
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;

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
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VLL A(M+1),B(M+1); FOR(i,1,M+1) cin >> A[i] >> B[i];
    ll K; cin >> K;
    VLL C(K); REP(i,K) cin >> C[i];

    // VVLL G(K+1, VLL(K+1, INF)); FOR(i,1,K+1) G[i][i] = 0LL;
    // FOR(k1,1,K) FOR(k2,k1+1,K+1) {
    //     FOR(i,1,M+1) {
    //         if (C[k1] == A[i] && C[k2] == B[i]) {
    //             G[k1][k2] = G[k2][k1] = 1;
    //         }
    //     }
    // }
    // warshall_floyd(G, K);
    // FOR(i,1,K+1) {
    //     cout << "------\n";
    //     cout << i << endl;
    //     FOR(j,i+1,K+1) {
    //         cout << G[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    VVE G(N);
    FOR(i,1,M+1) {
        G[A[i]-1].push_back(E(1, B[i]-1));
        G[B[i]-1].push_back(E(1, A[i]-1));
    }
    VVLL D(K,VLL(K,INF));
    VLL dist(N, INF);
    REP(i,K) {
        dijkstra(G, dist, C[i]-1);
        REP(j,K) if (C[i] != C[j]) D[i][j] = D[j][i] = dist[C[j]-1];
        REP(j,N) dist[j] = INF;
    }

    VVLL dp(1<<K, VLL(K, INF));
    REP(i,K) dp[1<<i][i] = 1;
    FOR(S,1,1<<K) {
        // if (__builtin_popcountll(S) <= 1) continue;
        // ll L, R;
        // REP(i,K) if (S & (1<<i)) { R = i; break; }
        // RREP(i,K) if (S & (1<<i)) { L = i; break; }
        REP(i,K) {
            if (S & (1<<i)) continue;
            REP(j,K) {
                if (!(S & (1<<j))) continue;
                chmin(dp[S+(1<<i)][i], dp[S][j] + D[j][i]);
            }
        }
    }
    ll ans = INF;
    REP(i,K) chmin(ans, dp[(1<<K)-1][i]);
    if (ans == INF) ans = -1;
    COUT(ans);


    return 0;
}
