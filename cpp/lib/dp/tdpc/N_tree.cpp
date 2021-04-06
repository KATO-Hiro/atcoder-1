#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll MOD = 1000000007;
// --------------------------------------------------------

// NOTE
//   - 全方位木 DP
//   - 制約的には O(N^2) の木 DP でも間に合う
//   - 類題: abc160_f (ほぼ同じ)


/**
 * @brief 全方位木 DP (Rerooting DP)
 * 
 * @tparam S モノイドの型 (結合律を満たし単位元が存在する代数構造)
 * @tparam (*op)(S,S) 二項演算
 * @tparam (*fv)(S,int) 頂点に対する関数 (第2引数は頂点番号)
 * @tparam (*fe)(S,int,int) 有向辺に対する関数 (第2引数は始点番号,第3引数は終点番号)
 * @tparam (*e)() 単位元
 */
template <class S, S (*op)(S, S), S (*fv)(S, int), S (*fe)(S, int, int), S (*e)()>
struct rerooting {
    int N;
    vector<vector<int>> G;
    vector<vector<S>> dp;  // dp[u][i] := u から出る i 番目の有向辺の先の部分木に対応する値
    vector<S> ans;  // ans[u] := u を根とした木に対する答え
    rerooting(int n) : N(n) {
        G.resize(N);
        dp.resize(N);
        ans.resize(N);
    }

    // add edges in both directions
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void build() {
        for (int i = 0; i < N; i++) {
            dp[i].resize(G[i].size());
        }
        dfs1(0, -1);
        dfs2(0, -1, e());
    }

    S dfs1(int u, int p) {
        S res = e();
        int m = G[u].size();
        for (int i = 0; i < m; i++) {
            int v = G[u][i];
            if (v == p) continue;
            dp[u][i] = dfs1(v, u);
            res = op(res, fe(dp[u][i], u, v));
        }
        return fv(res, u);
    }

    void dfs2(int u, int p, S px) {
        int m = G[u].size();
        for (int i = 0; i < m; i++) {
            if (G[u][i] == p) {
                dp[u][i] = px;
                break;
            }
        }
        vector<S> dp_R(m + 1);
        dp_R[m] = e();
        for (int i = m; 0 < i; i--) {
            dp_R[i - 1] = op(fe(dp[u][i - 1], u, G[u][i - 1]), dp_R[i]);
        }
        ans[u] = fv(dp_R[0], u);
        S dp_l = e();
        for (int i = 0; i < m; i++) {
            int v = G[u][i];
            if (v != p) dfs2(v, u, fv(op(dp_l, dp_R[i + 1]), u));
            dp_l = op(dp_l, fe(dp[u][i], u, v));
        }
    }

    S query(int u) {
        assert(0 <= u && u < N);
        return ans[u];
    }
};


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

combination Z;

// ans[u] := u を根とした時に u と連結する辺から描き始める場合の数
struct S { ll n; mint m; };  // (辺の数, 描き方の数)
S op(S a, S b) { return S{a.n + b.n, a.m * b.m}; };
S fv(S x, [[maybe_unused]] int u) { return S{x.n, x.m * Z.fact(x.n)}; };
S fe(S x, [[maybe_unused]] int s, [[maybe_unused]] int t) { return S{x.n + 1, x.m * Z.ifact(x.n + 1)}; };
S e() { return S{0, 1}; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    rerooting<S, op, fv, fe, e> re(N);
    REP(_,N-1) {
        ll a, b; cin >> a >> b;
        a--; b--;
        re.add_edge(a, b);
    }

    Z = combination(N);
    re.build();

    mint ans = 0;
    REP(u,N) ans += re.query(u).m;
    ans /= 2;  // ダブルカウント対処 (∵最初に描く辺について両端の頂点でダブルカウント)
    cout << ans << endl;


    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_tree
