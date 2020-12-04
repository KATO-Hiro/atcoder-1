#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define SZ(c) ((int)(c).size())
using P = pair<int,int>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------

struct E {
    int to; ll w;
};
using VE = vector<E>;
using VVE = vector<VE>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N; cin >> N;
    VVE G(N);
    int s, t; ll w;
    REP(_,N-1) {
        cin >> s >> t >> w;
        G[s].push_back(E{t, w});
        G[t].push_back(E{s, w});
    }

    VVLL dp(N);
    REP(u, N) dp[u] = VLL(SZ(G[u]), -1);
    auto rec = [&](auto f, int i, int j) -> ll {
        if (dp[i][j] >= 0) return dp[i][j];
        int u = G[i][j].to;
        ll w = G[i][j].w;
        ll res = w;
        REP(v, SZ(G[u])) {
            if (i == G[u][v].to) continue;
            chmax(res, w + f(f, u, v));
        }
        return dp[i][j] = res;
    };

    REP(i,N) {
        ll ans = 0;
        REP(j, SZ(G[i])) {
            chmax(ans, rec(rec, i, j));
        }
        cout << ans << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_B&lang=ja
