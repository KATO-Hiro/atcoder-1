#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VS = vector<string>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


// 回転 (2次元配列)
//   - 回転方向は反時計回り
//   - m = 1 (90度), m = 2 (180度), m = 3 (270度), m = others (no change)
VS rotate_2d(VS& A, ll m) {
    ll const H = (ll)A.size();
    ll const W = (ll)A[0].size();

    // 90度回転
    if (m == 1) {
        VS B(W, string(H, ' '));
        REP(h,H) REP(w,W) B[W-1-w][h] = A[h][w];
        return B;
    }

    // 180度回転
    if (m == 2) {
        VS B(H, string(W, ' '));
        REP(h,H) REP(w,W) B[H-1-h][W-1-w] = A[h][w];
        return B;
    }

    // 270度回転
    if (m == 3) {
        VS B(W, string(H, ' '));
        REP(h,H) REP(w,W) B[w][H-1-h] = A[h][w];
        return B;
    }

    // 0度回転
    VS B(A);
    return B;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, W; cin >> H >> W;
    VS S(H); REP(i,H) cin >> S[i];
    VS T(H); REP(i,H) cin >> T[i];

    ll h1 = INF, h2 = -INF, w1 = INF, w2 = -INF;
    REP(h,H) REP(w,W) if (T[h][w] == '#') {
        chmin(h1, h); chmin(w1, w); chmax(h2, h); chmax(w2, w);
    }
    ll HH = h2 - h1 + 1;
    ll WW = w2 - w1 + 1;
    auto is_ok = [&](VS& A) -> bool {
        ll Y = (ll)A.size();
        ll X = (ll)A[0].size();
        REP(sh,H-Y+1) REP(sw,W-X+1) {
            bool ok = true;
            REP(h,Y) REP(w,X) {
                if (S[sh+h][sw+w] == '#' && A[h][w] == '#') ok = false;
            }
            if (ok) return true;
        }
        return false;
    };

    VS U(HH,string(WW,' '));
    REP(h,HH) REP(w,WW) U[h][w] = T[h1+h][w1+w];
    REP(m,4) {
        VS X = rotate_2d(U, m);
        if (is_ok(X)) {
            cout << "Yes" << endl; return 0; 
        }
    }
    cout << "No" << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/past202012-open/tasks/past202012_e
