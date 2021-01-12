#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, W; cin >> H >> W;
    VVLL C(H+1, VLL(W+1)); FOR(h,1,H+1) FOR(w,1,W+1) cin >> C[h][w];

    VVLL dp(H+1, VLL(W+1, 0));
    FOR(h,1,H+1) FOR(w,1,W+1) if (C[h][w] != 1) {
        ll tmp = INF;
        chmin(tmp, dp[h][w-1]);
        chmin(tmp, dp[h-1][w]);
        chmin(tmp, dp[h-1][w-1]);
        chmax(dp[h][w], tmp + 1);
    }
    ll ans = 0;
    FOR(h,1,H+1) FOR(w,1,W+1) chmax(ans, dp[h][w]);
    ans = ans * ans;
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_A&lang=ja
