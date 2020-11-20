#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<int,int>;
using VI = vector<int>;
// --------------------------------------------------------

struct edge {
    int t, w;
};

P bfs(int N, vector<vector<edge>>& G, int s) {
    VI d(N+1,-1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    int u, v;
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (edge e : G[u]) {
            v = e.t;
            if (d[v] != -1) continue;
            d[v] = d[u] + e.w;
            q.push(v);
        }
    }

    int max_u = -1;
    int max_d = -1;
    FOR(u,0,N+1) {
        if (max_d < d[u]) {
            max_d = d[u];
            max_u = u;
        }
    }
    return P(max_u, max_d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N; cin >> N;
    vector<vector<edge>> G(N+1);
    REP(_,N-1) {
        int s, t, w; cin >> s >> t >> w;
        G[s].push_back(edge{t, w});
        G[t].push_back(edge{s, w});
    }

    int u, v, d;
    tie(u, d) = bfs(N, G, 1);
    tie(v, d) = bfs(N, G, u);

    cout << d << '\n';

    return 0;
}
