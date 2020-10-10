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
    cout << fixed << setprecision(10);

    ll H, W; cin >> H >> W;
    VS S(H + 2);
    S[0] = S[H+1] = string(W+2, '#');
    FOR(h,1,H+1) {
        string T; cin >> T;
        T = "#" + T + "#";
        S[h] = T;
    }

    ll K = 0;
    FOR(h,1,H+1) FOR(w,1,W+1) {
        if (S[h][w] == '.') K++;
    }
    debug(K)

    VVI U(H+2, VI(W+2, -1));
    VVI D(H+2, VI(W+2, -1));
    VVI L(H+2, VI(W+2, -1));
    VVI R(H+2, VI(W+2, -1));

    int hh, ww;
    int cnt;
    FOR(h,1,H+1) FOR(w,1,W+1) {
        if (S[h][w] == '#') continue;
        if (U[h][w] == -1) {
            hh = h; ww = w; cnt = 0;
            while (S[hh][ww] == '.') {
                U[hh++][ww] = cnt++;
            }
        }
        if (L[h][w] == -1) {
            hh = h; ww = w; cnt = 0;
            while (S[hh][ww] == '.') {
                L[hh][ww++] = cnt++;
            }
        }
    }

    for (int h = H; 0 <= h; --h) for (int w = W; 0 <= w; --w) {
        if (S[h][w] == '#') continue;
        if (D[h][w] == -1) {
            hh = h; ww = w; cnt = 0;
            while (S[hh][ww] == '.') {
                D[hh--][ww] = cnt++;
            }
        }
        if (R[h][w] == -1) {
            hh = h; ww = w; cnt = 0;
            while (S[hh][ww] == '.') {
                R[hh][ww--] = cnt++;
            }
        }
    }

    mint ans = 0;
    FOR(h,1,H+1) FOR(w,1,W+1) {
        if (S[h][w] == '#') continue;
        ll num = 1 + U[h][w] + D[h][w] + L[h][w] + R[h][w];
        ans += (mint(2).pow(num) - 1) * mint(2).pow(K - num);
    }
    cout << ans << '\n';

    return 0;
}
