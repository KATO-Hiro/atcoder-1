#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VI = vector<int>;
using VVI = vector<VI>;
static const int INF = (1 << 30) - 1;  // 1073741824 - 1
// --------------------------------------------------------


static const int MAX_N = 16;
VVI dp((1 << MAX_N), VI(MAX_N, INF));

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N, M; cin >> N >> M;
    VVI G(N, VI(N, INF));
    REP(_, M) {
        int s, t, d; cin >> s >> t >> d;
        G[s][t] = d;
    }

    // dp[T][v] --> dp[S][u] に遷移 (T + {u} = S)
    // - u ∈ S
    // - v ∈ T
    dp[0][0] = 0;  // 「各頂点を1度ずつ通る」であれば出発点によらず最終結果は同じ(∵閉路)
    FOR(S, 1, (1 << N)) {
        REP(u, N) {
            if (!(S & (1 << u))) continue;
            int T = S - (1 << u);
            REP(v, N) {
                if (T != 0 && !(T & (1 << v))) continue;  // この問題では消してよい (∵次行で弾かれる)
                if (G[v][u] == INF) continue;
                dp[S][u] = min(dp[S][u], dp[T][v] + G[v][u]);
            }
        }
    }

    int ans = dp[(1 << N) - 1][0];
    if (ans == INF) ans = -1;
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_A
