#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VS = vector<string>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll H, W; cin >> H >> W;
    VS S(H); REP(h,H) cin >> S[h];

    ll sh = 0, sw = 0, gh = 0, gw = 0;
    REP(h,H) REP(w,W) {
        if (S[h][w] == 's') {
            sh = h; sw = w;
        } else if (S[h][w] == 'g') {
            gh = h; gw = w;
        }
    }

    auto on_grid = [&](ll h, ll w) -> bool {
        return (h < 0 || H <= h || w < 0 || W <= w) ? false : true;
    };

    deque<P> d; d.push_front(P(sh, sw));
    VVLL dist(H, VLL(W, INF)); dist[sh][sw] = 0;
    static const VLL dh = {-1,1,0,0};
    static const VLL dw = {0,0,-1,1};
    ll h, w, hh, ww;
    ll cost;
    while (!d.empty()) {
        tie(h, w) = d.front(); d.pop_front();
        REP(i,4) {
            hh = h + dh[i];
            ww = w + dw[i];
            if (!on_grid(hh, ww)) continue;
            cost = (S[hh][ww] == '#') ? 1 : 0;
            if (chmin(dist[hh][ww], dist[h][w] + cost)) {
                // (cost == 0) ? d.push_front(P(hh,ww)) : d.push_back(P(hh,ww));
                if (cost == 0) {
                    d.push_front(P(hh, ww));
                } else {
                    d.push_back(P(hh, ww));
                }
            }
        }
    }
    string ans = dist[gh][gw] <= 2 ? "YES" : "NO";
    cout << ans << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/arc005/tasks/arc005_3
