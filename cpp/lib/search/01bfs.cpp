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
static const int INF = 1 << 30;  // 1073741824
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int H, W; cin >> H >> W;
    VS C(H); REP(h,H) cin >> C[h];

    int sh = 0, sw = 0, gh = 0, gw = 0;
    REP(h,H) REP(w,W) {
        if (C[h][w] == 's') {
            sh = h; sw = w;
        } else if (C[h][w] == 'g') {
            gh = h; gw = w;
        }
    }

    VVI dist(H, VI(W, INF));
    dist[sh][sw] = 0;
    deque<P> d;
    d.push_front(make_pair(sh, sw));
    int h, w;
    VI dh = {0,0,1,-1};
    VI dw = {1,-1,0,0};
    while (!d.empty()) {
        tie(h, w) = d.front(); d.pop_front();
        REP(i,4) {
            int hh = h + dh[i];
            int ww = w + dw[i];
            if (hh < 0 || H <= hh || ww < 0 || W <= ww) continue;
            int cost = C[hh][ww] == '#' ? 1 : 0;
            if (dist[h][w] + cost < dist[hh][ww]) {
                dist[hh][ww] = dist[h][w] + cost;
                if (cost == 0) {
                    d.push_front(make_pair(hh, ww));
                } else {
                    d.push_back(make_pair(hh, ww));
                }
            }
        }
    }
    string ans = dist[gh][gw] <= 2 ? "YES" : "NO";
    cout << ans << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/arc005/tasks/arc005_3
