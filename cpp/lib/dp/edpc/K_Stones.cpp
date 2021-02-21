#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VB = vector<bool>;
// --------------------------------------------------------

// NOTE
//   - ゲーム DP
//   - 蟻本 p.272 と同じ

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, K; cin >> N >> K;
    VLL A(N); REP(i,N) cin >> A[i];

    // dp[i] := 石が i 個ある場合の勝ち負け
    VB dp(K+1, false);
    FOR(i,1,K+1) {
        for (ll a : A) {
            if (0 <= i - a && !dp[i - a]) {
                dp[i] = true;
            }
        }
    }
    string ans = dp[K] ? "First" : "Second";
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_k
