#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
using P = pair<ll,ll>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


/**
 * @brief 二部グラフ判定
 * 
 * @param G 隣接グラフ
 * @return pair<bool,VLL> 
 * - bool: 二部グラフであるか
 * - VLL : 彩色結果 (true 時のみ有効な結果)
 */
pair<bool,VLL> is_bipartite_graph(const VVLL& G) {
    const ll N = (ll)G.size();

    VLL C(N,-1); C[0] = 0;
    queue<P> q; q.push(P(0,-1));
    while (!q.empty()) {
        auto [u, p] = q.front(); q.pop();
        for (ll v : G[u]) if (v != p) {
            if (C[v] != -1) {
                if (C[v] != (C[u] ^ 1)) return make_pair(false, C);
            } else {
                C[v] = C[u] ^ 1;
                q.push(P(v, u));
            }
        }
    }
    return make_pair(true, C);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VVLL G(N);
    REP(_,M) {
        ll A, B; cin >> A >> B;
        A--; B--;
        G[A].push_back(B);
        G[B].push_back(A);
    }

    auto [is_bipartite, C] = is_bipartite_graph(G);

    ll ans = 0;
    if (!is_bipartite) {  // 二部グラフでない ⇔ 奇数長サイクルが存在
        ans = N*(N-1)/2 - M;
    } else {
        ll n0 = count(ALL(C), 0);
        ll n1 = count(ALL(C), 1);
        ans = n0*n1 - M;
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_c
