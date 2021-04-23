#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
// --------------------------------------------------------


// 有向グラフのサイクル検知
// DAG であれば探索終了後に全頂点の入次数が0 (シンク) となるが，
// サイクルに含まれる頂点はシンクになり得ないことを利用して検知する
bool cycle_detection(const VVLL& G) {
    const ll N = (ll)G.size();

    VB in_cycle(N, true);
    VLL indeg(N, 0);  // indegree
    REP(u,N) for (ll v : G[u]) indeg[v]++;  // count indegree for each vertex

    queue<ll> q;  // set of vertices with 0 indegree
    REP(u,N) if (indeg[u] == 0) q.push(u);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        in_cycle[u] = false;
        for (ll v : G[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }
    REP(u,N) if (in_cycle[u]) return true;
    return false;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VVLL G(N);
    REP(_,M) {
        ll s, t; cin >> s >> t;
        // s--; t--;
        G[s].push_back(t);
    }

    ll ans = (cycle_detection(G) ? 1 : 0);
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A&lang=ja
