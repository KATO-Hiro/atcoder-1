#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

// NOTE
//   - ゲーム DP
//   - 後退解析

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll A, B; cin >> A >> B;
    VLL a(A); REP(i,A) cin >> a[i];
    VLL b(B); REP(i,B) cin >> b[i];

    // dp[l][r] := 左にl個・右にr個ある状態から始めて双方最善を尽くした場合の先手の価値合計
    VVLL dp(A+1, VLL(B+1,0));
    FOR(l,0,A+1) FOR(r,0,B+1) {
        if (l == 0 && r == 0) continue;
        ll num = (A + B) - (l + r);  // 今まで取られた数
        if (num % 2 == 0) {  // すぬけ
            if (0 <= l-1) chmax(dp[l][r], dp[l-1][r] + a[A-l]);
            if (0 <= r-1) chmax(dp[l][r], dp[l][r-1] + b[B-r]);
        } else {  // すめけ
            dp[l][r] = INF;
            if (0 <= l-1) chmin(dp[l][r], dp[l-1][r]);
            if (0 <= r-1) chmin(dp[l][r], dp[l][r-1]);
        }
    }
    ll ans = dp[A][B];
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_game
