#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<int,int>;
using VS = vector<string>;
using VI = vector<int>;
using VVI = vector<VI>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int H, W; cin >> H >> W;
    int sh, sw, gh, gw; cin >> sh >> sw >> gh >> gw; sh--; sw--; gh--; gw--;
    VS S(H); REP(h,H) cin >> S[h];
    // VVI A(H,VI(W)); REP(h,H) REP(w,W) cin >> A[h][w];

    auto on_grid = [&](int h, int w) -> bool {
        return (h < 0 || H <= h || w < 0 || W <= w) ? false : true;
    };

    queue<P> q; q.push(P(sh, sw));
    VVI dist(H, VI(W, -1)); dist[sh][sw] = 0;
    const VI dh = {0,0,1,-1};
    const VI dw = {1,-1,0,0};
    int h, w;
    while (!q.empty()) {
        tie(h, w) = q.front(); q.pop();
        REP(i,4) {
            int hh = h + dh[i];
            int ww = w + dw[i];
            if (!on_grid(hh, ww)) continue;
            if (S[hh][ww] == '#') continue;
            if (dist[hh][ww] != -1) continue;
            dist[hh][ww] = dist[h][w] + 1;
            q.push(P(hh, ww));
        }
    }
    cout << dist[gh][gw] << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/atc002/tasks/abc007_3
