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
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
template<class T> void debug_line(const vector<T>& ans, ll l, ll r, ll L = 0) { cerr << "l." << L << " :"; for (ll i = l; i < r; i++) { cerr << " " << ans[i]; } cerr << '\n'; }
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

    ll H, W; cin >> H >> W;
    VS A(H); REP(h,H) cin >> A[h];

    auto on_grid = [&](ll h, ll w) -> bool {
        return (h < 0 || H <= h || w < 0 || W <= w) ? false : true;
    };

    static const VLL dh = {1,0};
    static const VLL dw = {0,1};
    VVLL dp(H,VLL(W));
    VVB flag(H,VB(W,false));
    // turn : 0 は Takahashi, 1 = Aoki
    auto rec = [&](auto self, ll h, ll w, ll turn) -> ll {
        if (flag[h][w]) return dp[h][w];
        flag[h][w] = true;

        // ll res = 0;
        // if (A[h][w] == '+') {
        //     res += (turn == 0 ? 1 : -1);
        // } else {
        //     res += (turn == 0 ? -1 : 1);
        // }

        if (h == H-1 && w == W-1) {
            return dp[h][w] = 0;
        }

        ll res = (turn == 0 ? -INF : INF);
        REP(i,2) {
            ll hh = h + dh[i];
            ll ww = w + dw[i];
            if (!on_grid(hh, ww)) continue;

            if (turn == 0) {
                ll tmp = self(self, hh, ww, turn^1) + (A[hh][ww] == '+' ? 1 : -1);
                chmax(res, tmp);
            } else {
                ll tmp = self(self, hh, ww, turn^1) + (A[hh][ww] == '-' ? 1 : -1);
                chmin(res, tmp);
            }
        }
        return dp[h][w] = res;
    };

    ll ans = rec(rec, 0, 0, 0);
    if (ans > 0) {
        COUT("Takahashi");
    } else if (ans < 0) {
        COUT("Aoki");
    } else {
        COUT("Draw");
    }

    return 0;
}
