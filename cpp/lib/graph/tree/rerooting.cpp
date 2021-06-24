#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


// References:
//   <https://null-mn.hatenablog.com/entry/2020/04/14/124151>
//   <https://qiita.com/keymoon/items/2a52f1b0fb7ef67fb89e>
//   <https://hcpc-hokudai.github.io/archive/dynamic_programming_rerooting.pdf>
//   <https://algo-logic.info/tree-dp/>
//   <https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp> (for implementation)

/**
 * @brief 全方位木 DP (Rerooting DP)
 * 
 * @tparam S モノイドの型 (結合律を満たし単位元が存在する代数構造)
 * @tparam (*op)(S,S) 二項演算
 * @tparam (*fv)(S,int) 頂点に対する関数 (第2引数は頂点番号)
 * @tparam (*fe)(S,int,int,ll) 有向辺に対する関数 (第2/3引数は始点/終点番号,第4引数は重み)
 * @tparam (*e)() 単位元
 */
template <class S, S (*op)(S, S), S (*fv)(S, int), S (*fe)(S, int, int, ll), S (*e)()>
struct rerooting {
    struct edge { int to; ll w; };
    int N;
    vector<vector<edge>> G;
    vector<vector<S>> dp;  // dp[u][i] := u から出る i 番目の有向辺の先の部分木に対応する値
    vector<S> ans;  // ans[u] := u を根とした木に対する答え
    rerooting(int n) : N(n) {
        G.resize(N);
        dp.resize(N);
        ans.resize(N);
    }

    // 頂点 u から頂点 v に有向辺を張る
    //   - 無向グラフの場合は両方向を追加する
    void add_edge(int u, int v, ll w) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back({v, w});
    }

    void build() {
        for (int u = 0; u < N; u++) {
            dp[u].resize(G[u].size());
        }
        dfs1(0, -1);
        dfs2(0, -1, e());
    }

    S dfs1(int u, int p) {
        S res = e();
        int m = G[u].size();
        for (int i = 0; i < m; i++) {
            auto [v, w] = G[u][i];
            if (v == p) continue;
            dp[u][i] = dfs1(v, u);
            res = op(res, fe(dp[u][i], u, v, w));
        }
        return fv(res, u);
    }

    void dfs2(int u, int p, S px) {
        int m = G[u].size();
        for (int i = 0; i < m; i++) {
            if (G[u][i].to == p) {
                dp[u][i] = px;
                break;
            }
        }
        vector<S> dp_R(m+1);
        dp_R[m] = e();
        for (int i = m; 0 < i; i--) {
            auto [v, w] = G[u][i-1];
            dp_R[i-1] = op(fe(dp[u][i-1], u, v, w), dp_R[i]);
        }
        ans[u] = fv(dp_R[0], u);
        S dp_l = e();
        for (int i = 0; i < m; i++) {
            auto [v, w] = G[u][i];
            if (v != p) dfs2(v, u, fv(op(dp_l, dp_R[i+1]), u));
            dp_l = op(dp_l, fe(dp[u][i], u, v, w));
        }
    }

    S query(int u) {
        assert(0 <= u && u < N);
        return ans[u];
    }
};


// (rerooting) ans[u] := u を根とした時に u から最も遠い頂点までの距離
using S = ll;
S op(S a, S b) { return max(a, b); };
S fv(S x, [[maybe_unused]] int u) { return x; };
S fe(S x, [[maybe_unused]] int s, [[maybe_unused]] int t, ll w) { return x + w; };
S e() { return 0; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    rerooting<S, op, fv, fe, e> re(N);
    REP(_,N-1) {
        ll s, t, w; cin >> s >> t >> w;
        // s--; t--;
        re.add_edge(s, t, w);
        re.add_edge(t, s, w);
    }
    re.build();

    ll ans = 0;
    REP(u,N) chmax(ans, re.query(u));
    cout << ans << endl;

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=ja
