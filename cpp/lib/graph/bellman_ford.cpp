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


// 0-based index
// P := (cost, to)
bool bellman_ford(VVP& G, VLL& dist, ll s) {
    const ll N = (ll)G.size();
    assert(N == (ll)dist.size());
    assert(0 <= s && s < N);

    dist[s] = 0;
    REP(i,N) REP(u,N) {
        if (dist[u] == INF) continue;
        for (auto& [c, v] : G[u]) {
            if (chmin(dist[v], dist[u] + c)) {
                if (i == N-1) return true;
            }
        }
    }
    return false;
}

// 頂点 s から到達可能であるか否かの bool 配列を返す
//   「スタート地点からあるループを経由してゴール地点へ移動する」
//   が可能であるかを下記によって調べるために本メソッドは使用される想定
//     - スタート地点からそのループに到達できるか
//     - そのループからゴール地点に到達できるか
//   実装参考: <https://atcoder.jp/contests/abc137/submissions/18998862>
VB bfs(VVLL& G, ll s) {
    queue<ll> q; q.push(s);
    VB B(G.size(),false); B[s] = true;
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (ll v : G[u]) {
            if (B[v]) continue;
            B[v] = true;
            q.push(v);
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
        G[s].push_back(P(d, t));
    }

    VLL dist(N, INF);
    bool exist_negative_cycle = bellman_ford(G, dist, r);
    if (exist_negative_cycle) {
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
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B
