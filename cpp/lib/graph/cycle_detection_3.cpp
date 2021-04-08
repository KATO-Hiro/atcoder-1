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


// 無向グラフの閉路検出
//   ※多重辺は想定外
//   - 閉路が存在しない場合，サイズ 0 の vector を返す
//   - 閉路が存在する場合，最初に見つけた閉路の頂点配列を返す
//     e.g.) C = {u1, u2, u3} のとき u1 -> u2 -> u3 -> u1 となっている
VLL cycle_detection(VVLL& G) {
    const ll N = (ll)G.size();
    VLL C;
    VB visited(N,false);
    deque<ll> d;
    bool cycle = false;
    auto rec = [&](auto self, ll u, ll p) -> void {
        for (ll v : G[u]) if (v != p) {
            if (visited[v]) {
                // 閉路に無関係な頂点群を削除
                while (v != d.front()) { d.pop_front(); }

                // 閉路を構成する頂点群を回収
                while (!d.empty()){ C.push_back(d.front()); d.pop_front(); }

                cycle = true;
                return;
            }
            visited[v] = true;
            d.push_back(v);
            self(self, v, u);
            if (cycle) return;
            d.pop_back();
        }
    };
    rec(rec, 0, -1);
    return C;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);


    return 0;
}
// Verify: TODO
