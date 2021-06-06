#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// static const ll MOD = 1000000007;
static const ll MOD = 1000003;  // for ecr063_e
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


// References:
//   <https://drken1215.hatenablog.com/entry/2019/03/20/202800>


// Gauss Jordan の掃き出し法 (行列 A を標準形に変形する)
int GaussJordan(vector<vector<mint>>& A, bool is_extended = false) {
    int H = A.size(), W = A[0].size();
    int rank = 0;
    for (int w = 0; w < W; w++) {
        if (is_extended && w == W - 1) break;  // 拡大係数行列の最終列はスキップ

        int pivot = -1;
        for (int h = rank; h < H; h++) {
            if (A[h][w] != 0) { pivot = h; break; }
        }
        if (pivot == -1) continue;

        swap(A[pivot], A[rank]);

        // ピボットの値を 1 にする (逆元をかける)
        mint inv = A[rank][w].inv();
        for (int ww = 0; ww < W; ++ww)
            A[rank][ww] = A[rank][ww] * inv;

        // ピボットのある列を掃き出す
        for (int h = 0; h < H; ++h) if (h != rank) {
            if (A[h][w] != 0) {
                mint c = A[h][w];  // 掃き出したい列の係数
                for (int ww = 0; ww < W; ww++) {
                    A[h][ww] -= A[rank][ww] * c;
                }
            }
        }
        rank++;
    }
    return rank;
}

// 連立一次方程式 Ax = b を解く
pair<int,vector<mint>> linear_equation(const vector<vector<mint>>& A, const vector<mint>& b) {
    int H = A.size(), W = A[0].size();
    vector<vector<mint>> M(H, vector<mint>(W + 1));
    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) {
            M[h][w] = A[h][w];
        }
        M[h][W] = b[h];
    }
    int rank = GaussJordan(M, true);

    // 解が存在するか判定
    for (int h = rank; h < H; h++) {
        if (M[h][W] != 0) return make_pair(-1, vector<mint>(0));
    }

    vector<mint> res(W, 0);
    for (int h = 0; h < rank; h++) {
        res[h] = M[h][W];
    }
    return make_pair(rank, res);
}


int main() {
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll K = 10;
    VVM F(K+1, VM(K+1));
    VM B(K+1);

    REP(h,K+1) {
        REP(w,K+1) F[h][w] = mint(h).pow(w);

        cout << "? " << h << endl;
        ll fx; cin >> fx;
        assert(fx != -1);
        B[h] = fx;
    }

    auto [rank, A] = linear_equation(F, B);
    // 解の個数 = 2 ^ {p - rank}

    REP(x,MOD) {
        mint fx = 0;
        REP(k,K+1) fx += A[k] * mint(x).pow(k);
        if (fx == 0) {
            cout << "! " << x << endl;
            return 0;
        }
    }
    cout << "! -1" << endl;

    return 0;
}
// Verify: https://codeforces.com/contest/1155/problem/E
