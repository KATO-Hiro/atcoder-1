#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


void warshall_floyd(int N, vector<vector<int>> &G, int INF) {
    rep(k, N) rep(i, N) {
        if (G[i][k] == INF) continue;
        rep(j, N) {
            if (G[i][j] > G[i][k] + G[k][j]) {
                G[i][j] = G[i][k] + G[k][j];
            }
        }
    }
}


int main() {
    int N, M;
    cin >> N >> M;

    int INF = 1 << 30;
    vector<vector<int>> G(N, vector<int>(N, INF));
    rep(i, N) G[i][i] = 0;
    int a, b, t;
    rep(_, M) {
        cin >> a >> b >> t;
        a--; b--;
        G[a][b] = t;
        G[b][a] = t;
    }

    warshall_floyd(N, G, INF);

    int ans = INF;
    rep(i, N) {
        int max_dist = 0;
        rep(j, N) max_dist = max(max_dist, G[i][j]);
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