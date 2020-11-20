#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


void warshall_floyd(int N, VVLL& G) {
    FOR(k,1,N+1) {
        FOR(i,1,N+1) {
            if (G[i][k] == INF) continue;
            FOR(j,1,N+1) {
                if (G[k][j] == INF) continue;
                chmin(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
}


// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N, M; cin >> N >> M;
    VVLL G(N+1, VLL(N+1, INF));
    FOR(i,1,N+1) G[i][i] = 0LL;

    int s, t; ll d;
    REP(_, M) {
        cin >> s >> t >> d;
        s++; t++;  // For AOJ input type (0-based)
        G[s][t] = d;
    }

    warshall_floyd(N, G);

    // NEGATIVE CYCLE
    FOR(i,1,N+1) {
        if (G[i][i] < 0) {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }

    FOR(i,1,N+1) {
        FOR(j,1,N+1) {
            if (j != 1) cout << " ";
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
