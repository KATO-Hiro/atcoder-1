#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VS = vector<string>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, W; cin >> H >> W;
    ll sh, sw, gh, gw; cin >> sh >> sw >> gh >> gw;
    sh--; sw--; gh--; gw--;
    VS S(H); REP(h,H) cin >> S[h];
    // VVLL A(H,VLL(W)); REP(h,H) REP(w,W) cin >> A[h][w];

    auto on_grid = [&](ll h, ll w) -> bool {
        return (h < 0 || H <= h || w < 0 || W <= w) ? false : true;
    };

    queue<P> q; q.push(P(sh, sw));
    VVLL dist(H, VLL(W, -1)); dist[sh][sw] = 0;
    static const VLL dh = {-1,1,0,0};
    static const VLL dw = {0,0,-1,1};
    ll h, w, hh, ww;
    while (!q.empty()) {
        tie(h, w) = q.front(); q.pop();
        REP(i,4) {
            hh = h + dh[i];
            ww = w + dw[i];
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
