#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
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
// static const ll MOD = 1000000007;
static const ll MOD = 998244353;
static const int INF = 1 << 30;
// static const ll INF = 1LL << 62;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N, K; cin >> N >> K;

    VLL A(N + 1, 0);
    A[1] = 1;

    VI L(K), R(K);
    REP(i, K) cin >> L[i] >> R[i];

    FOR(i, 1, N) {
        A[i] = (A[i] + A[i - 1]) % MOD;
        ll a = A[i];
        REP(j, K) {
            int l = i + L[j];
            if (l > N) continue;
            A[l] = (A[l] + a) % MOD;
            int r = i + R[j] + 1;
            if (r > N) continue;
            A[r] = (MOD + A[r] - a) % MOD;
        }
    }
    ll ans = A[N];
    cout << ans << '\n';

    return 0;
}
