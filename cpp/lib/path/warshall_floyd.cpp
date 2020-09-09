#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
const int INF = 1 << 30;


void warshall_floyd(int N, vector<vector<int>> &G) {
    REP(k, N) REP(i, N) {
        if (G[i][k] == INF) continue;
        REP(j, N) {
            if (G[i][j] > G[i][k] + G[k][j]) {
                G[i][j] = G[i][k] + G[k][j];
            }
        }
    }
}


int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> G(N, vector<int>(N, INF));
    REP(i, N) G[i][i] = 0;
    int a, b, t;
    REP(_, M) {
        cin >> a >> b >> t;
        a--; b--;
        G[a][b] = t;
        G[b][a] = t;
    }

    warshall_floyd(N, G);

    int ans = INF;
    REP(i, N) {
        int max_dist = 0;
        REP(j, N) max_dist = max(max_dist, G[i][j]);
        ans = min(ans, max_dist);
    }
    cout << ans << endl;
    return 0;
}

/*
https://atcoder.jp/contests/abc012/tasks/abc012_4

input 3
-------
4 6
1 2 1
2 3 1
3 4 1
4 1 1
1 3 1
4 2 1

output 3
--------
1

*/