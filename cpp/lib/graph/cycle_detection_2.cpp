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
VLL cycle_detection(VVLL& G) {
    const ll N = (ll)G.size();
    VLL C;
    VB visited(N,false);
    VB visiting(N,false);  // 探索中の経路に含まれるか (deque に入っているか)
    deque<ll> d;
    bool cycle = false;
    REP(s,N) if (!visited[s]) {
        auto rec = [&](auto self, ll u) -> void {
            for (ll v : G[u]) {
                if (visiting[v]) {
                    // 閉路に無関係な頂点群を削除
                    while (v != d.front()) { d.pop_front(); }

                    // 閉路を構成する頂点群を回収
                    while (!d.empty()){ C.push_back(d.front()); d.pop_front(); }

                    cycle = true;
                    return;
                }
                visiting[v] = true; d.push_back(v);
                self(self, v);
                if (cycle) return;
                visiting[v] = false; d.pop_back();
                visited[v] = true;
            }
        };
        visiting[s] = true; d.push_back(s);
        rec(rec, d.back());
        if (cycle) return C;
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
        ll A, B; cin >> A >> B;
        A--; B--;
        G[A].push_back(B);
    }

    auto C = cycle_detection(G);
    if (SZ(C) == 0) { COUT(-1); return 0; }

    while (true) {
        ll L = SZ(C);
        unordered_set<ll> S; for (ll c : C) S.insert(c);
        S.erase(C[0]);
        bool ok = true;
        [&]() -> void {
            REP(i,L) {
                ll u = C[i];
                S.erase(C[(i+1) % L]);
                for (ll v : G[u]) {
                    if (!S.count(v)) continue;
                    ll k = -1; REP(j,L) if (C[j] == v) k = j;
                    VLL D; D.push_back(C[k]);
                    while (true) {
                        k = (k+1) % L;
                        D.push_back(C[k]);
                        if (k == i) break;
                    }
                    C = D;
                    ok = false;
                    return;
                }
                S.insert(C[i]);
            }
        }();
        if (ok) break;
    }
    COUT(SZ(C));
    for (ll c : C) COUT(c+1);

    return 0;
}
// Verify: https://atcoder.jp/contests/abc142/tasks/abc142_f
