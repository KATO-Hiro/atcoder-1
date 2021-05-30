#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
// --------------------------------------------------------

// References:
//   <https://drken1215.hatenablog.com/entry/2019/03/20/202800>


// NOTE: 問題に合わせて適切に設定する
//       (拡大係数行列を使う場合に W を制約ピッタリにするのは NG)
static const int MAX_H = 100000 + 10;
static const int MAX_W = 60 + 10;

// 最上位ビット ("左"から 0 桁目) が BitMat[:][0] に対応
// ※ 拡大係数行列で b 列を右側 (下位ビット側) に連結する場合があるため左右反転
struct BitMat {
    int H, W;
    bitset<MAX_W> val[MAX_H];
    BitMat(int _H, int _W) : H(_H), W(_W) {}
    inline bitset<MAX_W>& operator [] (int h) { return val[h]; }
};

// Gauss Jordan の掃き出し法 (行列 A を標準形に変形する)
int GaussJordan(BitMat& A, bool is_extended = false) {
    int H = A.H, W = A.W;
    int rank = 0;
    for (int w = 0; w < W; w++) {
        if (is_extended && w == W - 1) break;  // 拡大係数行列の最終列はスキップ

        int pivot = -1;
        for (int h = rank; h < H; ++h) {
            if (A[h][w]) { pivot = h; break; }
        }
        if (pivot == -1) continue;

        swap(A[pivot], A[rank]);

        // ピボットのある列を掃き出す (bitset 高速化)
        for (int h = 0; h < H; h++) if (h != rank) {
            if (A[h][w]) A[h] ^= A[rank];
        }
        rank++;
    }
    return rank;
}

// 連立一次方程式 Ax = b を解く
pair<int,vector<int>> linear_equation(BitMat& A, vector<int> b) {
    int H = A.H, W = A.W;
    BitMat M(H, W + 1);
    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) {
            M[h][w] = A[h][w];
        }
        M[h][W] = b[h];
    }
    int rank = GaussJordan(M, true);

    // 解が存在するか判定
    for (int h = rank; h < H; h++) {
        if (M[h][W]) return make_pair(-1, vector<int>(0));
    }

    vector<int> res(W, 0);
    for (int h = 0; h < rank; h++) {
        res[h] = M[h][W];
    }
    return make_pair(rank, res);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL A(N); REP(i,N) cin >> A[i];

    ll xor_A = 0;
    for (ll a : A) xor_A ^= a;

    ll M = 60;
    BitMat B(N, M);
    REP(d,M) {
        // 1 が奇数個の桁は任意の分け方で 2^d の寄与となるので無視
        if (BIT(xor_A,d)) continue;

        // 1 が偶数個の桁は奇数個ずつに分けられるか確認
        REP(i,N) if (BIT(A[i],d)) B[i][M-1-d] = 1;
    }
    GaussJordan(B, false);

    ll xor_B = 0;
    REP(d,M) {
        ll num = 0;
        REP(i,N) if (B[i][M-1-d]) num++;
        if (num % 2 == 1) xor_B += (1LL<<d);
    }

    ll ans = xor_A + 2*xor_B;
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc141/tasks/abc141_f
