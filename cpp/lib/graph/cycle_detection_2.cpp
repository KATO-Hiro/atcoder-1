#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((ll)(c).size())
#define COUT(c) cout << (c) << '\n'
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
// --------------------------------------------------------


// 有向グラフの閉路検出
//   ※自己ループ・多重辺は想定外
//   - 閉路が存在しない場合，サイズ 0 の vector を返す
//   - 閉路が存在する場合，最初に見つけた閉路の頂点配列を返す
//     e.g.) C = {u1, u2, u3} のとき u1 -> u2 -> u3 -> u1 となっている
VLL cycle_detection(const VVLL& G) {
    const ll N = (ll)G.size();
    VLL C;
    VB visited(N,false);   // 訪問済フラグ（有向サイクル検出なので 1 回の探索で十分）
    VB visiting(N,false);  // 探索中の経路に含まれるか (deque に入っているか)
    deque<ll> d;
    bool is_cycle = false;
    REP(s,N) if (!visited[s]) {
        auto rec = [&](auto self, ll u) -> void {
            if (visited[u]) return;
            for (ll v : G[u]) {
                if (visiting[v]) {
                    // 閉路に無関係な頂点群を削除
                    while (v != d.front()) { d.pop_front(); }

                    // 閉路を構成する頂点群を回収
                    while (!d.empty()){ C.push_back(d.front()); d.pop_front(); }

                    is_cycle = true;
                    return;
                }
                visiting[v] = true; d.push_back(v);
                self(self, v);
                if (is_cycle) return;
                visiting[v] = false; d.pop_back();
                visited[v] = true;
            }
        };
        visiting[s] = true; d.push_back(s);
        rec(rec, d.back());
        if (is_cycle) return C;
        visiting[s] = false; d.pop_back();
        visited[s] = true;
    }
    return C;  // 閉路が存在しなかったので空
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VVLL G(N);
    REP(_,M) {
        ll u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
    }

    auto C = cycle_detection(G);
    if (SZ(C) == 0) { COUT("YES"); return 0; }

    REP(i,SZ(C)) {
        ll u = C[i];
        ll v = C[(i+1) % SZ(C)];

        auto it = G[u].begin();
        while (*it != v) { it++; }
        G[u].erase(it);

        auto D = cycle_detection(G);
        if (SZ(D) == 0) { COUT("YES"); return 0; }

        G[u].push_back(v);
    }
    COUT("NO");

    return 0;
}
// Verify: https://codeforces.com/contest/915/problem/D
