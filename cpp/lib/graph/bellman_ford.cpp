#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


/**
 * @brief ベルマンフォード法
 *        - 0-based index
 *        - P := (to, cost)
 * 
 * @param G    隣接グラフ
 * @param dist 距離配列
 * @param s    始点
 * @return pair<bool, VLL> 
 * - bool: 負閉路が含まれるか
 * - VLL : 負閉路に含まれる頂点配列 (負閉路が含まれなければ空)
 */
pair<bool, VLL> bellman_ford(VVP& G, VLL& dist, ll s) {
    const ll N = (ll)G.size();
    assert(N == (ll)dist.size());
    assert(0 <= s && s < N);

    VLL loop;  // 負閉路に含まれる頂点配列
    dist[s] = 0;
    REP(i,N) REP(u,N) if (dist[u] != INF) {
        for (auto& [v, c] : G[u]) {
            if (chmin(dist[v], dist[u] + c)) {
                if (i == N-1) loop.push_back(v);
            }
        }
    }
    bool negative_cycle = (loop.size() > 0);
    return make_pair(negative_cycle, loop);
}

// 頂点 s から到達可能であるか否かの bool 配列を返す
//   「スタート地点からあるループを経由してゴール地点へ移動する」
//   が可能であるかを下記によって調べるために本メソッドは使用される想定
//     - スタート地点からそのループに到達できるか
//     - そのループからゴール地点に到達できるか
//   実装参考: <https://atcoder.jp/contests/abc061/submissions/21181308>
VB bfs(VVLL& G, ll s) {
    const ll N = (ll)G.size();
    assert(0 <= s && s < N);

    queue<ll> q; q.push(s);
    VB B(N,false); B[s] = true;
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (ll v : G[u]) if (!B[v]) {
            B[v] = true; q.push(v);
        }
    }
    return B;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, M, r; cin >> N >> M >> r;
    VVP G(N);
    REP(_,M) {
        ll s, t, d; cin >> s >> t >> d;
        // s--; t--;
        G[s].push_back(P(t, d));
    }

    VLL dist(N, INF);
    auto [negative_cycle, loop] = bellman_ford(G, dist, r);
    if (negative_cycle) {
        cout << "NEGATIVE CYCLE" << '\n';
    } else {
        REP(i, N) {
            if (dist[i] == INF) {
                cout << "INF" << '\n';
            } else {
                cout << dist[i] << '\n';
            }
        }
    }

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=ja
