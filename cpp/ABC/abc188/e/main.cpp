#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
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
    VLL A(N); REP(i,N) cin >> A[i];
    VVLL G(N);
    ll X, Y;
    REP(_,M) {
        cin >> X >> Y;
        X--; Y--;
        G[X].push_back(Y);
    }

    VLL indeg(N, 0);  // indegree
    REP(u, N) for (ll v : G[u]) indeg[v]++;  // count indegree for each vertex

    ll ans = -INF;
    VLL dp(N, INF);
    VB visited(N, false);
    auto rec = [&](auto f, ll u) {
        if (visited[u]) return dp[u];
        ll res = -INF;
        for (ll v : G[u]) {
            chmax(res, max(f(f, v), A[v]));
        }
        chmax(ans, res - A[u]);
        visited[u] = true;
        return dp[u] = res;
    };

    REP(i,N) {
        if (indeg[i] != 0) continue;
        rec(rec, i);
    }
    COUT(ans);

    return 0;
}
