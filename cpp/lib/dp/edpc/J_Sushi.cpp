#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
// --------------------------------------------------------

// NOTE
//   - 期待値 DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL A(N); REP(i,N) cin >> A[i];

    unordered_map<ll,ll> cnt;
    for (ll a : A) cnt[a]++;

    // dp[x][y][z] := 1 個の皿が x 個, 2 個の皿が y 個, 3 個の皿が z 個のとき
    //                全ての寿司がなくなるまでの操作回数の期待値
    VVVD dp(N+1,VVD(N+1,VD(N+1,-1)));
    dp[0][0][0] = 0;
    auto rec = [&](auto self, ll x, ll y, ll z) -> double {
        if (dp[x][y][z] > -0.5) return dp[x][y][z];
        ll n = x + y + z;
        double res = (double)N/n;  // 0個以外の皿を引くまでの操作回数の期待値 (1/(n/N))
        if (x) res += self(self, x-1, y,   z  ) * x / n;
        if (y) res += self(self, x+1, y-1, z  ) * y / n;
        if (z) res += self(self, x,   y+1, z-1) * z / n;
        return dp[x][y][z] = res;
    };
    double ans = rec(rec, cnt[1], cnt[2], cnt[3]);
    cout << ans << '\n';

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_j
