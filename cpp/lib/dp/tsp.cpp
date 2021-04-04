#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(n,i) ((n>>i) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, M; cin >> N >> M;
    VVLL G(N, VLL(N, INF));
    ll s, t, d;
    REP(_, M) {
        cin >> s >> t >> d;
        G[s][t] = d;
    }

    // dp[S][u] --> dp[T][v]  配るDP
    //   - u ∈ S
    //   - v ∈ T = S + {v}
    // 出発点が指定されていない場合，「各頂点を1度ずつ通る」であれば出発点によらず
    // 最終結果は同じであるため (∵閉路)，頂点1を出発点とした場合のみ解けば十分
    VVLL dp(1<<N, VLL(N, INF));
    dp[0][0] = 0;
    REP(S,1<<N) {
        REP(u,N) {  // TSP は出発点に戻るため dp[0][0] で初期化 ⇒ BIT(S,u) は NG
            REP(v,N) if (!BIT(S,v)) {
                ll T = S | (1<<v);
                chmin(dp[T][v], dp[S][u] + G[u][v]);
            }
        }
    }
    ll ans = dp[(1<<N) - 1][0];
    if (ans == INF) ans = -1;
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A
