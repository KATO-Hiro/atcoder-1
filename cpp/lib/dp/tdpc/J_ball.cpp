#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
using VD = vector<double>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

// NOTE
//   - 期待値 DP
//   - 類題: past202012_k

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL x(N); REP(i,N) cin >> x[i];

    const ll M = 16;
    // dp[S] := 物の分布が S であるときの投球回数の期待値の最小値
    VD dp(1<<M,-1); dp[0] = 0;
    auto rec = [&](auto self, ll S) -> double {
        if (dp[S] > -0.5) return dp[S];
        double res = INF;
        REP(i,M) {
            ll n = 0;
            for (ll j : {-1,0,1}) if (i+j >= 0 && BIT(S,i+j)) n++;
            if (n == 0) continue;
            double tmp = (double)3/n;
            for (ll j : {-1,0,1}) if (i+j >= 0 && BIT(S,i+j)) {
                tmp += (double)self(self, S^(1<<(i+j))) / n;
            }
            chmin(res, tmp);
        }
        return dp[S] = res;
    };

    ll S = 0; REP(i,N) S |= (1<<x[i]);
    double ans = rec(rec, S);
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_ball
