#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll A, B; cin >> A >> B;

    auto solve = [](ll X) -> ll {
        if (X == -1) return 0;

        string N = to_string(X);
        ll L = SZ(N);
        N = " " + N;

        // i 桁目まで見た時 N が条件を満たしているか
        // (no two adjacent digits are the same)
        bool ok = true;

        VVLL dp(L+1, VLL(10,0));
        FOR(i,1,L+1) {
            ll n = N[i] - '0';

            // 先頭に非ゼロが初登場 (< N)
            if (1 < i) FOR(d,1,10) dp[i][d] += 1;

            // N 一致状態 -> N 未満確定状態
            if (ok) {
                ll nn = N[i-1] - '0';
                REP(d,n) {
                    if (i == 1 && d == 0) continue;  // leading zero 回避
                    if (d != nn) dp[i][d] += 1;
                }
            }

            // N 未満確定状態間の遷移
            REP(d1,10) REP(d2,10) if (d1 != d2) dp[i][d2] += dp[i-1][d1];

            // i 桁目まで見た時 N が条件を満たしているか
            if (N[i-1] == N[i]) ok = false;
        }

        ll res = 0;

        // x = 0
        if (0 < X) res += 1;

        // 0 < x < N
        REP(d,10) res += dp[L][d];

        // x = N
        if (ok) res++;

        return res;
    };

    ll ans = solve(B) - solve(A-1);
    cout << ans << endl;

    return 0;
}
// verify: https://cses.fi/problemset/task/2220
