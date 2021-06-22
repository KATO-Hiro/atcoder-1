#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
// --------------------------------------------------------

// References:
//   <https://en.wikipedia.org/wiki/Knight%27s_tour>


struct KnightTour {
    const int N = 8;
    const vector<int> dh = {-2,-1, 1, 2, 2, 1,-1,-2};
    const vector<int> dw = { 1, 2, 2, 1,-1,-2,-2,-1};
    int H, W;
    vector<vector<int>> G;
    vector<vector<int>> grid;
    vector<int> degree;
    KnightTour(int H_, int W_) : H(H_), W(W_) {
        G.resize(H*W);
        grid.resize(H, vector<int>(W, 0));
        degree.resize(H*W, 0);
        for (int h = 0; h < H; h++) {
            for (int w = 0; w < W; w++) {
                int u = hw2pos(h, w);
                for (int i = 0; i < N; i++) {
                    int hh = h + dh[i];
                    int ww = w + dw[i];
                    if (hh < 0 || H <= hh || ww < 0 || W <= ww) continue;
                    int v = hw2pos(hh, ww);
                    G[u].push_back(v);
                }
            }
        }
    }

    void init() {
        for (int h = 0; h < H; h++) {
            for (int w = 0; w < W; w++) {
                int u = hw2pos(h, w);
                degree[u] = G[u].size();
                grid[h][w] = 0;
            }
        }
    }

    int hw2pos(int h, int w) { return h * W + w; }
    pair<int,int> pos2hw(int pos) { return make_pair(pos / W, pos % W); };

    // ヒューリスティックを用いて移動先の候補を列挙
    //   [Warnsdorff's rule] 移動可能なマスが最も少ないマスを列挙する
    vector<int> next_moves(int u) {
        vector<int> res;
        int min_move = 12345;
        for (int v : G[u]) {
            auto [h, w] = pos2hw(v);
            if (grid[h][w] != 0) continue;  // already visited
            if (chmin(min_move, degree[v])) {
                res = {v};
            } else if (min_move == degree[v]) {
                res.push_back(v);
            }
        }
        return res;
    }

    // 始点 (sh, sw) から Knight's Tour を解く
    pair<bool, vector<vector<int>>> solve(int sh, int sw) {
        init();
        int k = 1;
        grid[sh][sw] = k++;
        bool solved = false;
        auto dfs = [&](auto self, int u) -> void {
            if (k > H*W) { solved = true; return; }
            for (int v : next_moves(u)) {
                auto [h, w] = pos2hw(v);
                degree[u]--; degree[v]--; grid[h][w] = k++;
                self(self, v);
                if (solved) { return; }
                degree[u]++; degree[v]++; grid[h][w] = 0; k--;
            }
        };
        dfs(dfs, hw2pos(sh, sw));
        return make_pair(solved, grid);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll H = 8, W = 8;
    KnightTour kt(H, W);

    ll sh, sw; cin >> sw >> sh;
    sh--; sw--;
    auto [solved, ans] = kt.solve(sh, sw);
    if (solved) {
        REP(h,H) cout_line(ans[h],0,W);
    } else {
        assert(false);
    }

    return 0;
}
// Verify: https://cses.fi/problemset/task/1689
