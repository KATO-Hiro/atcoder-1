#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (int i = (r)-1; (l) <= i; --i)
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
#define SZ(c) ((int)(c).size())
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << #x << " = " << (x) << '\n';
using PP = pair<int,int>;
using VP = vector<PP>;
// using VVP = vector<VP>;
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
static const int INF = (1 << 30) - 1;  // 1073741824 - 1
// static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N; cin >> N;
    VI P(N+1); FOR(i,1,N+1) cin >> P[i];

    VP memo;

    ll L = 0;
    ll R = 0;
    FOR(i,1,N+1) {
        if (P[i] < i) {
            L += (ll)(i - P[i]);
            memo.push_back(PP(i-1, (i - P[i])));
        } else if (i < P[i]) {
            R += (ll)(P[i] - i);
        }
    }

    if (L != R || L != N-1) {
        COUT(-1); return 0;
    }

    VI ans(N-1);
    int i = 0;
    for (auto p : memo) {
        int x = p.first;
        int n = p.second;
        REP(_,n) {
            ans[i++] = x--;
        }
    }

    VI check(ans);
    SORT(check);
    REP(i,N-1) {
        if (i+1 != check[i]) {
            COUT(-1);
            return 0;
        }
    }

    REP(i,N-1) {
        swap(P[ans[i]], P[ans[i]+1]);
    }
    FOR(i,1,N+1) {
        if (i != P[i]) {
            COUT(-1);
            return 0;
        }
    }

    for (int x : ans) {
        cout << x << '\n';
    }

    return 0;
}
