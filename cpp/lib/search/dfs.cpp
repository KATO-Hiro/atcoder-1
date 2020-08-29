#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


void dfs(int H, int W, int sy, int sx, vector<string> &c, vector<vector<bool>> &visited) {
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    stack<pair<int,int>> s;
    s.push(make_pair(sy, sx));
    int h, w, y, x;
    while (!s.empty()) {
        tie(h, w) = s.top(); s.pop();
        visited[h][w] = true;
        for (auto p: directions) {
            y = h + p[0];
            x = w + p[1];
            if (y < 0 || H <= y || x < 0 || W <= x) continue;
            if (c[h][w] == '#') continue;
            if (visited[y][x]) continue;
            s.push(make_pair(y, x));
        }
    }
}


int main() {
    int H, W;
    cin >> H >> W;
    vector<string> c(H);
    rep(h, H) cin >> c[h];

    int sy, sx, gy, gx;
    rep(h, H) rep(w, W) {
        if (c[h][w] == 's') { sy = h; sx = w;}
        if (c[h][w] == 'g') { gy = h; gx = w;}
    }

    vector<vector<bool>> visited(H, vector<bool>(W, false));
    dfs(H, W, sy, sx, c, visited);
    cout << (visited[gy][gx] ? "Yes" : "No") << endl;

    return 0;
}


/*
https://atcoder.jp/contests/atc001/tasks/dfs_a

Input 1
-------
4 5
s####
....#
#####
#...g

Output 1
--------
No

*/