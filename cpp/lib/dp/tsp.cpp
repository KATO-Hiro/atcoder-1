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

    // dp[T][v] --> dp[S][u] に遷移 (T + {u} = S)
    // - u ∈ S
    // - v ∈ T
    VVLL dp((1 << N), VLL(N, INF));
    // 出発点が指定されていない場合，「各頂点を1度ずつ通る」であれば出発点によらず
    // 最終結果は同じであるため (∵閉路)，ここでは簡単のため頂点1のみ出発点とする
    dp[0][0] = 0;
    FOR(S, 1, (1 << N)) {
        REP(u, N) {
            if (!(S & (1 << u))) continue;
            ll T = S - (1 << u);
            REP(v, N) {
                if (T != 0 && !(T & (1 << v))) continue;  // この問題では消してよい (∵次行で弾かれる)
                if (G[v][u] == INF) continue;
                dp[S][u] = min(dp[S][u], dp[T][v] + G[v][u]);
            }
        }
    }
    ll ans = dp[(1 << N) - 1][0];
    if (ans == INF) ans = -1;
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A
