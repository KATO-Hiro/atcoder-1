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
// static const int INF = 1 << 30;  // 1073741824
static const ll INF = 1LL << 62;  // 4611686018427387904
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N, M; cin >> N >> M;
    VLL H(N+1,0); FOR(i,1,N+1) cin >> H[i];
    VLL W(M+1,0); FOR(i,1,M+1) cin >> W[i];

    SORT(H);
    SORT(W);

    VLL L(N+2,0);
    for (int i = 2; i < N; i += 2) {
        L[i] += L[i-2] + llabs(H[i] - H[i-1]);
    }
    VLL R(N+2,0);
    for (int i = N-1; 2 <= i; i -= 2) {
        R[i] += R[i+2] + llabs(H[i] - H[i+1]);
    }

    ll ans = INF;
    FOR(i,1,M+1) {
        ll w = W[i];
        auto it = lower_bound(ALL(H), w);
        int idx = it - H.begin();
        if (idx % 2 == 0) {
            chmin(ans, L[idx-2] + llabs(w - H[idx-1]) + R[idx]);
        } else {
            chmin(ans, L[idx-1] + llabs(w - H[idx]) + R[idx+1]);
        }
    }
    cout << ans << '\n';

    return 0;
}
