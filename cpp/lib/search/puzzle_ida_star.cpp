#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


struct PuzzleIDAStar {
    struct Puzzle {
        vector<int> f;
        int space, sum_d;
        Puzzle() {}
        Puzzle(int N2_) { f.resize(N2_); }
    };
    const vector<int> dh = {1,0,-1,0};
    const vector<int> dw = {0,1,0,-1};
    vector<vector<int>> dist;  // マンハッタン距離 (ヒューリスティック用)
    int H, W, N2, L;
    Puzzle state, init;
    vector<int> moves;

    PuzzleIDAStar(int H_, int W_, int L_) : H(H_), W(W_), L(L_) {
        N2 = H * W;
        init = Puzzle(N2);
        moves.assign(L, -1);
        dist.resize(N2,vector<int>(N2));
        for (int i = 0; i < N2; i++) {
            for (int j = 0; j < N2; j++) {
                auto [h1, w1] = pos2hw(i);
                auto [h2, w2] = pos2hw(j);
                dist[i][j] = abs(h1 - h2) + abs(w1 - w2);
            }
        }
    }

    int hw2pos(int h, int w) { return h * W + w; }
    pair<int,int> pos2hw(int pos) { return make_pair(pos / W, pos % W); };

    void set_init(int h, int w, int n) {
        assert(0 <= h && h < H);
        assert(0 <= w && w < W);
        assert(0 <= n && n < N2);
        init.f[hw2pos(h,w)] = n;
        if (n == 0) {
            init.f[hw2pos(h,w)] = N2;
            init.space = hw2pos(h,w);
        }
    }

    int get_h(const Puzzle& pz) {
        int sum = 0;
        for (int i = 0; i < N2; i++) if (pz.f[i] != N2) {
            sum += dist[i][pz.f[i] - 1];
        }
        return sum;
    }

    bool dfs(int depth, int limit, int prev_r) {
        if (state.sum_d == 0) return true;
        if (depth + state.sum_d > limit) return false;  // IDA*
        auto [sh, sw] = pos2hw(state.space);
        int s = state.space;
        Puzzle tmp(N2);
        for (int r = 0; r < 4; r++) {
            if (max(prev_r, r) - min(prev_r, r) == 2) continue;  // 往復は無駄
            int th = sh + dh[r];
            int tw = sw + dw[r];
            if (th < 0 || H <= th || tw < 0 || W <= tw) continue;
            tmp = state;
            int t = hw2pos(th,tw);
            state.sum_d -= dist[t][state.f[t] - 1];
            state.sum_d += dist[s][state.f[t] - 1];
            swap(state.f[t], state.f[s]);
            state.space = t;
            if (dfs(depth + 1, limit, r)) { moves[depth] = r; return true; }
            state = tmp;
        }
        return false;
    }

    pair<int,vector<int>> solve() {
        init.sum_d = get_h(init);
        for (int limit = init.sum_d; limit <= L; limit++) {
            state = init;
            if (!dfs(0, limit, -123)) continue;
            int depth = 0;
            for (int i = L-1; 0 <= i; i--) {
                if (moves[i] != -1) { depth = i + 1; break; }
            }
            return make_pair(depth, moves);
        }
        return make_pair(-1, moves);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll H = 4;
    ll W = 4;
    ll L = 100;  // limit

    PuzzleIDAStar puzzle(H, W, L);

    REP(h,H) REP(w,W) {
        ll n; cin >> n;
        puzzle.set_init(h, w, n);
    }

    auto [ans, moves] = puzzle.solve();
    cout << ans << endl;

    return 0;
}
// Verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_13_C&lang=ja
