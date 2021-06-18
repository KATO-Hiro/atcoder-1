#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
#define COUT(c) cout << (c) << '\n'
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VLL = vector<ll>;
using VB = vector<bool>;
// --------------------------------------------------------


// References:
//   <https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html>

// 負閉路を一つ見つける : O(NM)
//   ※自己ループ・多重辺は想定外
//   - 負閉路が存在しない場合，サイズ 0 の vector を返す
//   - 負閉路が存在する場合，最初に見つけた負閉路の頂点配列を返す
//     e.g.) C = {s, v, ... , s} のとき s -> v -> ... -> s となっている
VLL find_negative_cycle(const VVP& G) {
    const ll N = (ll)G.size();

    // N 回ループした時に最短距離が更新される頂点を一つ探索
    ll s = -1;
    VLL dist(N,0);
    VLL from(N,-1);
    REP(i,N) {
        s = -1;
        REP(u,N) for (auto [v, c] : G[u]) {
            if (chmin(dist[v], dist[u] + c)) {
                from[v] = u; s = v;
            }
        }
    }
    if (s == -1) { return VLL(0); }  // 負閉路が存在しなかったので空

    // 遷移元を辿ることで負閉路を構築する
    VLL cycle;
    REP(_,N) { s = from[s]; }  // 確実に負閉路へ移動
    for (ll u = s;; u = from[u]) {
        cycle.push_back(u);
        if (u == s && cycle.size() > 1) break;
    }
    reverse(cycle.begin(), cycle.end());
    return cycle;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VVP G(N);
    REP(_,M) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        G[a].push_back(P(b, c));
    }

    VLL C = find_negative_cycle(G);
    if (SZ(C) == 0) { COUT("NO"); return 0; }

    REP(i,SZ(C)) C[i]++;

    COUT("YES");
    cout_line(C,0,SZ(C));

    return 0;
}
// verify: https://cses.fi/problemset/task/1197
