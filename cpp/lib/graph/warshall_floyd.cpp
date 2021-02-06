#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


// 0-based index
void warshall_floyd(VVLL& G) {
    const ll N = (ll)G.size();

    REP(k,N) {
        REP(i,N) if (G[i][k] != INF) {
            REP(j,N) if (G[k][j] != INF) {
                chmin(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, M; cin >> N >> M;
    VVLL G(N, VLL(N, INF)); REP(i,N) G[i][i] = 0LL;
    REP(_,M) {
        ll s, t, d; cin >> s >> t >> d;
        G[s][t] = d;
    }

    warshall_floyd(G);

    // NEGATIVE CYCLE
    REP(i,N) {
        if (G[i][i] < 0) {
            cout << "NEGATIVE CYCLE" << '\n';
            return 0;
        }
    }

    REP(i,N) {
        REP(j,N) {
            if (j) cout << " ";
            if (G[i][j] == INF) {
                cout << "INF";
            } else {
                cout << G[i][j];
            }
        }
        cout << '\n';
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C
