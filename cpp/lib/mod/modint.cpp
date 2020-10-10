#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
// --------------------------------------------------------


// References:
//   mint:
//     <https://github.com/atcoder/live_library/blob/master/mint.cpp>
//     <https://noshi91.hatenablog.com/entry/2019/03/31/174006>
//     <https://ei1333.github.io/luzhiled/snippets/math/mod-int.html>
//     <https://gist.github.com/MiSawa/dc78c3eb3ca16051818759ea069e8ccb>
//     <https://github.com/drken1215/algorithm/blob/master/MathCombinatorics/mod.cpp>
//   combination:
//     <https://github.com/atcoder/live_library/blob/master/comb.cpp>
//     <https://github.com/drken1215/algorithm/blob/master/MathCombinatorics/mod.cpp>

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

    constexpr mint C(int n, int k) const noexcept {
        if (n < 0 || k < 0 || n < k) return 0;
        return fact_[n] * ifact_[n-k] * ifact_[k];
    }
    constexpr mint H(int n, int k) const noexcept {
        if (n < 0 || k < 0) return 0;
        assert(n + k - 1 <= n_);
        return C(n + k - 1, k);
    }
    constexpr mint fact(int n) const noexcept {
        if (n < 0) return 0;
        return fact_[n];
    }
    constexpr mint ifact(int n) const noexcept {
        if (n < 0) return 0;
        return ifact_[n];
    }
    constexpr mint inv(int n) const noexcept {
        if (n < 0) return 0;
        return inv_[n];
    }
};


// Combination with repetition
// Verify: https://atcoder.jp/contests/abc021/tasks/abc021_d
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N, K; cin >> N >> K;

    combination comb(N + K - 1);
    cout << comb.H(N, K) << '\n';

    return 0;
}


// Combination
/*
// Verify: https://atcoder.jp/contests/abc034/tasks/abc034_c
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int W, H; cin >> W >> H;
    W--; H--;

    combination comb(W + H);
    mint ans = comb.C(W + H, W);
    // mint ans = comb.fact(W + H) * comb.ifact(W) * comb.ifact(H);

    cout << ans << '\n';

    return 0;
}
*/

// modint
/*
// Verify: https://atcoder.jp/contests/abc178/tasks/abc178_c
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N; cin >> N;
    mint ans = mint(10).pow(N) - mint(2) * mint(9).pow(N) + mint(8).pow(N);
    cout << ans << '\n';

    return 0;
}
*/
