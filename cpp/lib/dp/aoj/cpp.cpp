#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


// Chinese Postman Problem (CPP)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;

    VVLL G(N, VLL(N,INF)); REP(i,N) G[i][i] = 0;
    VLL D(N,0);  // 次数カウント用
    ll total = 0;
    REP(_,M) {
        ll s, t, d; cin >> s >> t >> d;
        // G[s][t] = G[t][s] = d;
        chmin(G[s][t], d);  // 多重辺の対処
        chmin(G[t][s], d);  // 多重辺の対処
        D[s]++; D[t]++;
        total += d;
    }

    // 奇点グラフを作成
    VLL odds;  // 奇点 (次数が奇数の頂点) の配列
    REP(u,N) if (D[u] % 2 == 1) odds.push_back(u);
    ll n = SZ(odds);
    assert(n % 2 == 0);  // 握手補題により偶数であることが保証される
    VVLL W(n, VLL(n,INF));  // 奇点グラフ

    // 奇点間の最短経路を求めて完全グラフを得る (Warshall Floyd)
    // ※ 奇点以外の頂点を経由してもよいため W ではなく G で計算
    //    ---> これ以降，G は全点対最短経路を表す (破壊的変更がなされる)
    REP(k,N) {
        REP(i,N) if (G[i][k] != INF) {
            REP(j,N) if (G[k][j] != INF) {
                chmin(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
    REP(i,n-1) FOR(j,i+1,n) {
        W[i][j] = W[j][i] = G[odds[i]][odds[j]];
    }

    // 奇点の完全グラフにおける最小重みマッチングを bit DP で解く
    // dp[T] --> dp[S] に遷移 (T + {u,v} = S)
    // - u,v ∈ S
    // - u,v ∉ T
    // ※マッチングなのでペアごと遷移 (頂点数が偶数であることは握手補題により保証)
    VLL dp(1<<n, INF);
    dp[0] = 0;
    REP(S,1<<n) {
        REP(u,n-1) FOR(v,u+1,n) if (BIT(S,u) && BIT(S,v)) {
            ll T = S - (1<<u) - (1<<v);
            chmin(dp[S], dp[T] + W[u][v]);
        }
    }

    ll ans = total + dp[(1<<n) - 1];
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_B&lang=ja
