#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

// NOTE
//   - ゲーム
//   - 後退解析
//   - 区間DPっぽいが違う (いわゆる原始的なDP？)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL A(N); REP(i,N) cin >> A[i];

    // dp[l][r] := 区間 [l,r] の数列における双方最善を尽くした場合の X-Y の値
    VVLL dp(N+1, VLL(N+1, INF));
    REP(l,N) dp[l][l] = (N % 2 == 1) ? A[l] : -A[l];
    auto rec = [&](auto f, ll l, ll r, bool is_first) -> ll {
        if (dp[l][r] != INF) return dp[l][r]; 
        bool next = !is_first;
        if (is_first) {
            return dp[l][r] = max(f(f,l+1,r,next) + A[l], f(f,l,r-1,next) + A[r]);
        } else {
            return dp[l][r] = min(f(f,l+1,r,next) - A[l], f(f,l,r-1,next) - A[r]);
        }
    };
    ll ans = rec(rec, 0, N-1, true);
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_l
