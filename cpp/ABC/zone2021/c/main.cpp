#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
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
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define COUNT(c,v) count(ALL(c),(v))
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) (((b)>>(i)) & 1)
#define PCNT(b) __builtin_popcountll(b)
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << "l." << __LINE__ << " : " << #x << " = " << (x) << '\n'
ll llceil(ll a, ll b) { return (a + b - 1) / b; }
ll bitlen(ll b) { if (b <= 0) { return 0; } return (64LL - __builtin_clzll(b)); }
string toupper(const string& S) { string T(S); REP(i,SZ(T)) T[i] = toupper(T[i]); return T; }
string tolower(const string& S) { string T(S); REP(i,SZ(T)) T[i] = tolower(T[i]); return T; }
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VVS = vector<VS>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VVVLL = vector<VVLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VVVB = vector<VVB>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
using VLD = vector<ld>;
using VVLD = vector<VLD>;
using VVVLD = vector<VVLD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL A(N,VLL(5)); REP(i,N) REP(j,5) cin >> A[i][j];

    auto is_ok = [&](ll X) -> bool {
        ll res = false;
        VLL C(5);
        auto rec = [&](auto self, ll n) -> void {
            if (n == 5) {
                bool ok1 = false;
                bool ok2 = false;
                bool ok3 = false;
                REP(i,N) {
                    bool b1 = true;
                    bool b2 = true;
                    bool b3 = true;
                    REP(j,5) {
                        if (C[j] == 0) { if (A[i][j] < X) b1 = false; }
                        if (C[j] == 1) { if (A[i][j] < X) b2 = false; }
                        if (C[j] == 2) { if (A[i][j] < X) b3 = false; }
                    }
                    if (b1) ok1 = true;
                    if (b2) ok2 = true;
                    if (b3) ok3 = true;
                }
                if (ok1 && ok2 && ok3) res = true;
                return;
            }
            REP(i,3) {
                C[n] = i;
                self(self, n+1);
            }
            return;
        };
        rec(rec, 0);
        return res;
    };

    ll ok = 0;
    ll ng = 1e10;
    while (ng - ok > 1) {
        ll m = (ok + ng) / 2;
        (is_ok(m) ? ok : ng) = m;
    }
    ll ans = ok;
    COUT(ans);

    return 0;
}
