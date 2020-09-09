#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
const ll INF = 1LL << 62;
// --------------------------------------------------------


void warshall_floyd(int N, vector<vector<ll>> &G) {
    REP(k, N) REP(i, N) {
        if (G[i][k] == INF) continue;
        REP(j, N) {
            if (G[k][j] == INF) continue;
            if (G[i][j] > G[i][k] + G[k][j]) {
                G[i][j] = G[i][k] + G[k][j];
            }
        }
    }
}


// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int V, E; cin >> V >> E;

    VVLL G(V, VLL(V, INF));
    REP(i, V) G[i][i] = 0LL;

    REP(_, E) {
        ll s, t, d; cin >> s >> t >> d;
        G[s][t] = d;
    }
    
    warshall_floyd(V, G);

    bool is_negative_cycle = false;
    REP(i, V) {
        if (G[i][i] < 0) is_negative_cycle = true;
    }
    if (is_negative_cycle) {
        cout << "NEGATIVE CYCLE" << '\n';
    } else {
        REP(i, V) {
            REP(j, V) {
                if (j) cout << " ";
                if (G[i][j] == INF) {
                    cout << "INF";
                } else {
                    cout << G[i][j];
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
