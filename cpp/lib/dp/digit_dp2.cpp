#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll MOD = 1000000007;
// --------------------------------------------------------


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
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll D; cin >> D;
    string N; cin >> N;

    ll L = SZ(N);
    N = " " + N;

    VVM dp(L+1,VM(D, 0));
    ll m = 0;  // N の 桁和 (mod D)
    FOR(i,1,L+1) {
        ll n = N[i] - '0';

        // 1) 先頭に非ゼロが初登場 (< N)
        if (1 < i) FOR(d,1,10) dp[i][d % D] += 1;

        // 2) N 一致状態 -> N 未満確定状態
        REP(d,n) {
            if (i == 1 && d == 0) continue;  // leading zero 回避
            dp[i][(m + d) % D] += 1;
        }

        // 3) N 未満確定状態間の遷移
        REP(d,10) REP(r,D) dp[i][(r + d) % D] += dp[i-1][r];

        m = (m + n) % D;
    }

    mint ans = 0;

    // 1) x = 0
    // 正整数なので該当なし

    // 2) 0 < x < N
    ans += dp[L][0];

    // 3) x = N
    if (m == 0) ans += 1;

    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/tdpc/tasks/tdpc_number
