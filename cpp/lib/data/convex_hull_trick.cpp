#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VB = vector<bool>;
using VLL = vector<ll>;
// --------------------------------------------------------


// References:
//   <https://smijake3.hatenablog.com/entry/2018/06/16/144548>
//   <https://tjkendev.github.io/procon-library/cpp/convex_hull_trick/li_chao_tree.html>
//   <https://cp-algorithms.com/geometry/convex_hull_trick.html>

/**
 * @brief Convex Hull Trick (Li-Chao Segment Tree)
 * 
 */
struct LiChaoSegtree {
    static const ll INF1 = 1e9;   // 葉ノード以外のダミー座標
    static const ll INF2 = 1e18;  // 最小値クエリの初期値
    ll N;          // 座標の数
    VLL xs, p, q;  // 座標・傾き・接線
    VB used;       // ノードが一度も使用されていなければ false

    LiChaoSegtree(ll n, const VLL& ps) {
        N = 1;
        while (N < n) N <<= 1;

        xs.resize(2*N);
        p.resize(2*N);
        q.resize(2*N);
        used.resize(2*N);

        REP(i,n) xs[i] = ps[i];
        FOR(i,n,2*N) xs[i] = INF1;
        REP(i,2*N) used[i] = false;
    }

    // 区間 [l,r) に対する直線 (a,b) の追加処理
    void _add_line(ll a, ll b, ll k, ll l, ll r) {
        while (l < r) {
            if(!used[k]) {
                used[k] = true; p[k] = a; q[k] = b;
                return;
            }

            ll m = (l + r) / 2;
            ll lx = xs[l], mx = xs[m], rx = xs[r-1];
            ll pk = p[k], qk = q[k];
            bool left  = (a*lx + b < pk*lx + qk);
            bool mid   = (a*mx + b < pk*mx + qk);
            bool right = (a*rx + b < pk*rx + qk);

            if (left && right) {  // 直線 (a,b) が全勝
                p[k] = a;
                q[k] = b;
                return;
            } else if (!left && !right) {  // 直線 (p,q) が全勝
                return;
            } else if (mid) {  // swap することで探索区間を片側だけに減らすテク
                swap(p[k], a);
                swap(q[k], b);
            } else if (left != mid) {  // [l,m) で直線 (a,b) が勝つ部分あり
                k = 2*k + 1; r = m;
            } else {  // [m,r) で直線 (a,b) が勝つ部分あり
                k = 2*k + 2; l = m;
            }
        }
    }

    // 直線 (a,b) の追加
    void add_line(ll a, ll b) { _add_line(a, b, 0, 0, N); }

    // 区間 [x_l, x_r) に対する線分 (a,b) の追加
    void add_segment_line(ll a, ll b, ll l, ll r) {
        ll L = l + N, R = r + N;
        ll sz = 1;
        while (L < R) {
            if (L & 1) {
                _add_line(a, b, L-1, l, l+sz);
                L++; l += sz;
            }
            if (R & 1) {
                R--; r -= sz;
                _add_line(a, b, R-1, r, r+sz);
            }
            L >>= 1; R >>= 1;
            sz <<= 1;
        }
    }

    // i 番目の座標に対する最小値を返す
    ll query(ll i) {
        ll x = xs[i];
        ll k = i + (N - 1);
        ll res = (used[k] ? p[k]*x + q[k] : INF2);
        while (k > 0) {
            k = (k - 1) / 2;
            if (used[k]) chmin(res, p[k]*x + q[k]);
        }
        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL a(N); REP(i,N) cin >> a[i];
    VLL x(N); REP(i,N) cin >> x[i];
    VLL y(N); REP(i,N) cin >> y[i];

    LiChaoSegtree cht(N, a);

    // dp[i] :=  左から i 番目までを考えた時の最小コスト
    // ----- 遷移式 --> Convex Hull Trick -----
    // dp[i] = min_{0<=j<i} {dp[j] + (x_j - a_{i-1})^2 + y_j^2}
    //       = min_{0<=j<i} { -2*x_j*a_{i-1} + (dp[j] + x_j^2 + y_j^2) } + a_{i-1}^2
    ll dp = 0;
    REP(i,N) {
        cht.add_line(-2*x[i], dp + x[i]*x[i] + y[i]*y[i]);
        dp = cht.query(i) + a[i]*a[i];
    }
    cout << dp << endl;

    return 0;
}
// Verify: https://yukicoder.me/problems/no/703
