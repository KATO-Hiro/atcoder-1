#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


/**
 * @brief 全方位木 DP (Rerooting DP)
 * 
 * @tparam S モノイドの型 (結合律を満たし単位元が存在する代数構造)
 * @tparam (*op)(S,S) 二項演算
 * @tparam (*fv)(S,int) 頂点に対する関数 (第2引数は頂点番号)
 * @tparam (*fe)(S,int,int) 有向辺に対する関数 (第2引数は始点番号,第3引数は終点番号)
 * @tparam (*e)() 単位元
 */
template <class S, S (*op)(S, S), S (*fv)(S, int), S (*fe)(S, int, int), S (*e)()>
struct rerooting {
    int N;
    vector<vector<int>> G;
    vector<vector<S>> dp;  // dp[u][i] := u から出る i 番目の有向辺の先の部分木に対応する値
    vector<S> ans;  // ans[u] := u を根とした木に対する答え
    rerooting(int n) : N(n) {
        G.resize(N);
        dp.resize(N);
        ans.resize(N);
    }

    // add edges in both directions
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void build() {
        for (int i = 0; i < N; i++) {
            dp[i].resize(G[i].size());
        }
        dfs1(0, -1);
        dfs2(0, -1, e());
    }

    S dfs1(int u, int p) {
        S res = e();
        int m = G[u].size();
        for (int i = 0; i < m; i++) {
            int v = G[u][i];
            if (v == p) continue;
            dp[u][i] = dfs1(v, u);
            res = op(res, fe(dp[u][i], u, v));
        }
        return fv(res, u);
    }

    void dfs2(int u, int p, S px) {
        int m = G[u].size();
        for (int i = 0; i < m; i++) {
            if (G[u][i] == p) {
                dp[u][i] = px;
                break;
            }
        }
        vector<S> dp_R(m + 1);
        dp_R[m] = e();
        for (int i = m; 0 < i; i--) {
            dp_R[i - 1] = op(fe(dp[u][i - 1], u, G[u][i - 1]), dp_R[i]);
        }
        ans[u] = fv(dp_R[0], u);
        S dp_l = e();
        for (int i = 0; i < m; i++) {
            int v = G[u][i];
            if (v != p) dfs2(v, u, fv(op(dp_l, dp_R[i + 1]), u));
            dp_l = op(dp_l, fe(dp[u][i], u, v));
        }
    }

    S query(int u) {
        assert(0 <= u && u < N);
        return ans[u];
    }
};

// NOTE
//   - 全方位木 DP

ll N, M;

// ans[u] := u を根とした時に u が黒であるような頂点の色の組み合わせ数
using S = ll;
S op(S a, S b) { return a * b % M; };
S fv(S a, [[maybe_unused]] int u) { return a; };
S fe(S x, [[maybe_unused]] int s, [[maybe_unused]] int t) { return (x + 1) % M; };
S e() { return 1; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    cin >> N >> M;
    rerooting<S, op, fv, fe, e> re(N);
    REP(_,N-1) {
        ll x, y; cin >> x >> y;
        x--; y--;
        re.add_edge(x, y);
    }

    re.build();
    REP(u,N) {
        cout << re.query(u) << '\n';
    }

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_v
