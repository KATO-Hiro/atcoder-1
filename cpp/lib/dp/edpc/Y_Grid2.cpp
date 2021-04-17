#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
using P = pair<ll,ll>;
using VP = vector<P>;
static const ll MOD = 1000000007;
// --------------------------------------------------------

// NOTE
//   - 包除原理 DP

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


struct combination {
    vector<mint> fact_, ifact_, inv_;
    int n_;
    combination() {}
    combination(int n) : fact_(n+1,0), ifact_(n+1,0), inv_(n+1,0) {
        assert(n != 0);
        assert(n < MOD);
        n_ = n;
        fact_[0] = 1; fact_[1] = 1;
        ifact_[0] = 1; ifact_[1] = 1;
        inv_[1] = 1;
        for(int i = 2; i <= n; ++i) {
            fact_[i] = fact_[i-1] * i;
            inv_[i] = -inv_[MOD%i] * (MOD/i);
            ifact_[i] = ifact_[i-1] * inv_[i];
        }
    }

    mint P(const int& n, const int& k) const noexcept {
        if (n < 0 || k < 0 || n < k) return 0;
        return fact_[n] * ifact_[n-k];
    }
    mint C(const int& n, const int& k) const noexcept {
        if (n < 0 || k < 0 || n < k) return 0;
        return fact_[n] * ifact_[n-k] * ifact_[k];
    }
    mint H(const int& n, const int& k) const noexcept {
        if (n < 0 || k < 0) return 0;
        assert(n + k - 1 <= n_);
        return C(n + k - 1, k);
    }
    mint fact(const int& n) const noexcept {
        assert(n <= n_);
        if (n < 0) return 0;
        return fact_[n];
    }
    mint ifact(const int& n) const noexcept {
        assert(n <= n_);
        if (n < 0) return 0;
        return ifact_[n];
    }
    mint inv(const int& n) const noexcept {
        assert(n <= n_);
        if (n < 0) return 0;
        return inv_[n];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, W, N; cin >> H >> W >> N;
    VP rc(N); REP(i,N) cin >> rc[i].first >> rc[i].second;

    SORT(rc);
    combination Z(H + W);

    // dp[i] := 壁を通り抜けることを許容した場合に
    //          最初に通り抜ける壁が i 番目である場合の数
    VM dp(N,0);
    REP(i,N) {
        auto& [r, c] = rc[i];
        dp[i] = Z.C(r-1 + c-1, r-1);
        REP(j,i) {
            auto& [rr, cc] = rc[j];
            if (rr > r || cc > c) continue;
            dp[i] -= dp[j] * Z.C(r-rr + c-cc, r-rr);
        }
    }

    mint ans = Z.C(H-1 + W-1, H-1);
    REP(i,N) {
        auto& [r, c] = rc[i];
        ans -= dp[i] * Z.C(H-r + W-c, H-r);
    }
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_y
