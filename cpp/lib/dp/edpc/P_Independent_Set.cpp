#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;
using VM = vector<mint>;

// NOTE
//   - 木 DP
//   - 類題: ABC036-D (全く同じ)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL G(N+1);
    ll x, y;
    REP(_,N-1) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    // 頂点 1 を根とする
    VM dp1(N+1, -1);  // dp1[i] := 頂点 i を根とする部分木で頂点 i を白で塗る場合の数
    VM dp2(N+1, -1);  // dp2[i] := 頂点 i を根とする部分木で頂点 i を黒で塗る場合の数
    auto rec = [&](auto f, ll u, ll p, ll c) -> mint {
        if (c == 1 && dp1[u] != -1) return dp1[u];
        if (c == 2 && dp2[u] != -1) return dp2[u];
        mint res = 1;
        for (ll v : G[u]) {
            if (v == p) continue;
            if (c == 1) {
                res *= (f(f, v, u, 1) + f(f, v, u, 2));
            } else {
                res *= f(f, v, u, 1);
            }
        }
        return (c == 1 ? dp1[u] : dp2[u]) = res;
    };
    ll ans = (rec(rec, 1, -1, 1) + rec(rec, 1, -1, 2)).val();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/dp/tasks/dp_p
