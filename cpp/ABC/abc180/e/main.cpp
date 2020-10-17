#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define MIN(c) *min_element(ALL(c))
#define MAX(c) *max_element(ALL(c))
#define SUM(c) accumulate(ALL(c), 0)
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((int)(c).size())
#define debug(x) cerr << #x << " = " << (x) << '\n';
using P = pair<int,int>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VD = vector<double>;
using VVD = vector<VD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
static const int INF = 1 << 30;  // 1073741824
// static const ll INF = 1LL << 62;  // 4611686018427387904
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


static const int MAX_N = 17;
VVI dp((1 << MAX_N), VI(MAX_N, INF));

struct city {
    int X, Y, Z;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N; cin >> N;


    vector<city> C(N);
    REP(i, N) {
        int X, Y, Z; cin >> X >> Y >> Z;
        C[i] = city{X, Y, Z};
    }

    VVI G(N, VI(N, INF));
    REP(i, N-1) FOR(j,i+1,N) {
        city a = C[i];
        city b = C[j];
        G[i][j] = abs(b.X - a.X) + abs(b.Y - a.Y) + max(0, b.Z - a.Z);
        G[j][i] = abs(a.X - b.X) + abs(a.Y - b.Y) + max(0, a.Z - b.Z);
    }

    dp[0][0] = 0;
    FOR(S, 1, (1 << N)) {
        FOR(u, 0, N) {
            if (!(S & (1 << u))) continue;
            int T = S - (1 << u);
            FOR(v, 0, N) {
                if (G[v][u] == INF) continue;
                dp[S][u] = min(dp[S][u], dp[T][v] + G[v][u]);
            }
        }
    }
    int ans = dp[(1 << N) - 1][0];
    cout << ans << '\n';

    return 0;
}
