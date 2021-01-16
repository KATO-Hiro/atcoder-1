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
// static const ll MOD = 1000000007;
static const ll MOD = 998244353;
// static const int INF = (1 << 30) - 1;  // 1073741824 - 1
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


struct mint {
    ll x;
    constexpr mint(ll x = 0) noexcept : x((x % MOD + MOD) % MOD) {}

    constexpr mint& operator+=(const mint& a) noexcept {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    constexpr mint& operator-=(const mint& a) noexcept {
        if ((x += MOD - a.x) >= MOD) x -= MOD;
        return *this;
    }
    constexpr mint& operator*=(const mint& a) noexcept { (x *= a.x) %= MOD; return *this; }
    constexpr mint& operator/=(const mint& a) noexcept { return *this *= a.inv(); }

    constexpr mint operator-() const noexcept { return mint(-x); }
    constexpr mint operator+(const mint& a) const noexcept { return mint(*this) += a; }
    constexpr mint operator-(const mint& a) const noexcept { return mint(*this) -= a; }
    constexpr mint operator*(const mint& a) const noexcept { return mint(*this) *= a; }
    constexpr mint operator/(const mint& a) const noexcept { return mint(*this) /= a; }
    constexpr bool operator==(const mint& a) const noexcept { return x == a.x; }
    constexpr bool operator!=(const mint& a) const noexcept { return x != a.x; }

    constexpr mint pow(ll n) const {
        if (n == 0) return 1;
        mint res = pow(n >> 1);
        res *= res;
        if (n & 1) res *= *this;
        return res;
    }
    constexpr mint inv() const { return pow(MOD - 2); }

    friend istream& operator>>(istream& is, mint& a) noexcept {
        ll v; is >> v;
        a = mint(v);
        return is;
    }
    friend ostream& operator<<(ostream& os, const mint& a) noexcept {
        return os << a.x;
    }
};
using VM = vector<mint>;
using VVM = vector<VM>;
using VVVM = vector<VVM>;
using VVVVM = vector<VVVM>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, W, K; cin >> H >> W >> K;
    VVLL A(H,VLL(W,-1));
    ll R = 0, D = 1, X = 2;
    REP(_,K) {
        ll h, w; cin >> h >> w;
        h--; w--;
        char c; cin >> c;
        if (c == 'R') {
            A[h][w] = R;
        } else if (c == 'D') {
            A[h][w] = D;
        } else {
            A[h][w] = X;
        }
    }

    // VVLL WL(H,VLL(W,0));
    // VVLL WR(H,VLL(W,0));
    VVLL HU(H,VLL(W,0));
    VVLL HD(H,VLL(W,0));
    // REP(h,H) {
    //     ll num = 0;
    //     REP(w,W) {
    //         WL[h][w] = num;
    //         if (A[h][w] == -1) num++;
    //     }
    //     num = 0;
    //     RREP(w,W) {
    //         WR[h][w] = num;
    //         if (A[h][w] == -1) num++;
    //     }
    // }
    REP(w,W) {
        ll num = 0;
        REP(h,H) {
            HU[h][w] = num;
            if (A[h][w] == -1) num++;
        }
        num = 0;
        RREP(h,H) {
            HD[h][w] = num;
            if (A[h][w] == -1) num++;
        }
    }

    ll M = max(H, W);
    VM pow3(M+1,1); REP(i,M) pow3[i+1] = pow3[i] * 3;
    VVM dp(H,VM(W,0));
    dp[0][0] = 1;
    REP(h,H) {
        REP(w,W) {
            if (h == H-1 && w == W-1) continue;
            if (w+1 < W && A[h][w] != D) {
                ll x = (A[h][w] == -1) ? 2 : 1;
                dp[h][w+1] += dp[h][w] * x * pow3[HD[h][w] + HU[h][w+1]];
            }
            if (h+1 < H && A[h][w] != R) {
                ll x = (A[h][w] == -1) ? 2 : 1;
                dp[h+1][w] += dp[h][w] * x;
                // dp[h+1][w] += dp[h][w] * x * pow3[WR[h][w] + WL[h+1][w]];
            }
        }
    }
    mint ans = dp[H-1][W-1];
    if (A[H-1][W-1] == -1) ans = ans * 3;
    COUT(ans);

    // REP(h,H) REP(w,W) COUT(dp[h][w]);

    return 0;
}
