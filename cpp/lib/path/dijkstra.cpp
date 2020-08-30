#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


void dijkstra(int N, vector<vector<P>> &G, int s, vector<int> &dist) {
    dist[s] = 0;
    priority_queue<P, vector<P>, greater<P>> p_queue;
    p_queue.push(make_pair(dist[s], s));
    int min_dist, dist_u, u, v, c, alt;
    while (!p_queue.empty()) {
        tie(min_dist, u) = p_queue.top(); p_queue.pop();
        dist_u = dist[u];
        if (dist_u < min_dist) continue;

        for (auto vc: G[u]) {
            tie(v, c) = vc;
            alt = dist_u + c;
            if (alt < dist[v]) {
                dist[v] = alt;
                p_queue.push(make_pair(alt, v));
            }
        }
    }
}


int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<P>> G(N, vector<P>());
    int a, b, t;
    rep(_, M) {
        cin >> a >> b >> t;
        a--; b--;
        G[a].push_back(make_pair(b, t));
        G[b].push_back(make_pair(a, t));
    }

    int INF = 1 << 30;
    int ans = INF;
    rep(s, N) {
        vector<int> dist(N, INF);
        dijkstra(N, G, s, dist);
        int max_dist = 0;
        rep(i, N) max_dist = max(max_dist, dist[i]);
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