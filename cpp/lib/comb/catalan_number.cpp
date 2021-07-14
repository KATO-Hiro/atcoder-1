#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
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
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll n; cin >> n;
    if (n % 2 == 1) { cout << 0 << endl; return 0; }
    ll N = n/2;

    combination Z(2*N);
    mint ans = Z.C(2*N, N) / (N+1);

    cout << ans << endl;

    return 0;
}
// Verify: https://cses.fi/problemset/task/2064
