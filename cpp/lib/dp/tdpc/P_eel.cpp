#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;
using VVM = vector<VM>;
using VVVM = vector<VVM>;

// NOTE
//   - 木 DP

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, K; cin >> N >> K;
    VVLL G(N);
    REP(_,N-1) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // dp[u][k][t] := 頂点 u を根とする部分木において，
    //                disjoint なパスが k 本があり，
    //                頂点 u の隣接辺 (親方向は除く) のうち
    //                disjoint なパスの一部である隣接辺が t 本である場合の数
    //                (t = 0,1,2)
    VVVM dp(N+1, VVM(K+1, VM(3, 0)));
    VVVM dp2(N+1, VVM(2*K+2, VM(3, 0)));  // 部分問題の dp 計算用
    auto dfs = [&](auto self, ll u, ll p) -> void {
        // 子を根とする部分木における部分問題を前計算しておく
        VLL ch;
        for (ll v : G[u]) if (v != p) {
            self(self, v, u);
            ch.push_back(v);
        }
        ll sz = ch.size();

        // 初期化
        REP(i,sz+1) REP(k,2*K+1) REP(t,3) dp2[i][k][t] = 0;
        dp2[0][0][0] = 1;

        // 子を一つずつ見ながら部分和 DP
        REP(i,sz) REP(k1,K+1) REP(k2,K+1) {
            ll k3 = k1 + k2;
            ll c = ch[i];

            // c 方向の隣接辺を disjoint なパスに使わない場合
            REP(t1,3) REP(t2,3) {
                dp2[i+1][k3][t1] += dp2[i][k1][t1] * dp[c][k2][t2];
            }

            // c 方向の隣接辺を disjoint なパスに使う場合
            if (true)   dp2[i+1][k3+1][1] += dp2[i][k1][0] * dp[c][k2][0];  // c からパス生成
            if (true)   dp2[i+1][k3  ][1] += dp2[i][k1][0] * dp[c][k2][1];  // c の子からパスを伸ばす
            if (true)   dp2[i+1][k3  ][2] += dp2[i][k1][1] * dp[c][k2][0];  // c からパス生成して dp2 に接続
            if (0 < k3) dp2[i+1][k3-1][2] += dp2[i][k1][1] * dp[c][k2][1];  // c の子からパスを伸ばして dp2 に接続
        }
        REP(k,K+1) REP(t,3) dp[u][k][t] = dp2[sz][k][t];
    };
    dfs(dfs, 0, -1);

    mint ans = 0;
    REP(t,3) ans += dp[0][K][t];
    cout << ans.val() << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_eel
