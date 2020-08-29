#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


void bfs(int H, int W, int sy, int sx, vector<string> &c, vector<vector<int>> &dist) {
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    queue<pair<int,int>> q;
    q.push(make_pair(sy, sx));
    dist[sy][sx] = 0;
    int h, w, y, x;
    while (!q.empty()) {
        tie(h, w) = q.front(); q.pop();
        for (auto p: directions) {
            y = h + p[0];
            x = w + p[1];
            if (y < 0 || H <= y || x < 0 || W <= x) continue;
            if (c[y][x] == '#') continue;
            if (dist[y][x] != -1) continue;
            dist[y][x] = dist[h][w] + 1;
            q.push(make_pair(y, x));
        }
    }
}


int main() {
    int H, W, sy, sx, gy, gx;
    cin >> H >> W >> sy >> sx >> gy >> gx;
    sy--; sx--; gy--; gx--;
    vector<string> c(H);
    rep(h, H) cin >> c[h];

    vector<vector<int>> dist(H, vector<int>(W, -1));
    bfs(H, W, sy, sx, c, dist);
    int ans = dist[gy][gx];
    cout << ans << endl;

    return 0;
}

/*
https://atcoder.jp/contests/atc002/tasks/abc007_3

Input 1
-------
7 8
2 2
4 5
########
#......#
#.######
#..#...#
#..##..#
##.....#
########

Output 1
--------
11

*/