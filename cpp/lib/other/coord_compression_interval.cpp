#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


/**
 * @brief 座標圧縮 (区間)
 * 
 * @param X1 区間の始点配列の参照 (圧縮後の座標に書き換えられる)
 * @param X2 区間の終点配列の参照 (圧縮後の座標に書き換えられる)
 * @param min_x 座標が取り得る最小値 (例: MIN(X1,X2) or 制約から決定)
 * @param max_x 座標が取り得る最大値 (例: MAX(X1,X2) or 制約から決定)
 * @param ds 確保する座標の調整値配列 (default: {-1, 0, 1})
 *           (1) 区間のみ必要な場合は ds = {0} で十分
 *               --> 区間の面積を求める場合など
 *           (2) 区間同士の間隔も必要な場合は ds = {-1,0,1} (問題により {0,1} も可)
 *               --> 線分で分けられた各領域を探索する場合など（連結性が重要な場合）
 * @return VLL 圧縮前の座標配列 (圧縮後の座標と1対1対応)
 */
VLL compress_interval(VLL& X1, VLL& X2, ll min_x, ll max_x, VLL ds = {-1, 0, 1}) {
    const ll N = SZ(X1);
    VLL XS;  // 圧縮前の座標配列 (圧縮後の座標と1対1対応)

    // 必要最小限の座標のみ抽出 (ds = {-1,0,1} の場合は3点ずつ確保)
    for (auto& X : {X1, X2}) {
        REP(i,N) {
            for (ll d : ds) {
                ll tx = X[i] + d;
                if (min_x <= tx && tx <= max_x) XS.push_back(tx);
            }
        }
    }
    // 重複削除
    SORT(XS);
    XS.erase(unique(ALL(XS)), XS.end());

    // 圧縮後の座標の割り当て
    REP(i,N) {
        X1[i] = lower_bound(ALL(XS), X1[i]) - XS.begin();
        X2[i] = lower_bound(ALL(XS), X2[i]) - XS.begin();
    }
    return XS;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL X1(N),Y1(N),X2(N),Y2(N);
    REP(i,N) cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];

    ll min_v = -1e9;
    ll max_v = +1e9;
    VLL ds = {0};  // メモリに余裕があればデフォルト {-1, 0, 1} が無難
    auto XS = compress_interval(X1, X2, min_v, max_v, ds);
    auto YS = compress_interval(Y1, Y2, min_v, max_v, ds);

    ll H = SZ(YS);
    ll W = SZ(XS);

    // S[h][w] > 0 を満たす (h,w) が存在する場合，
    // (h,w) を左上頂点とする (圧縮座標系の) 単位正方形が存在することを表す
    VVLL S(H, VLL(W, 0));
    REP(i,N) {
        S[Y1[i]][X1[i]]++;
        S[Y2[i]][X1[i]]--;
        S[Y1[i]][X2[i]]--;
        S[Y2[i]][X2[i]]++;
    }
    REP(w,W) FOR(h,1,H) S[h][w] += S[h-1][w];
    REP(h,H) FOR(w,1,W) S[h][w] += S[h][w-1];

    ll ans = 0;
    REP(h,H-1) REP(w,W-1) if (S[h][w] > 0) {
        ll dx = XS[w+1] - XS[w];
        ll dy = YS[h+1] - YS[h];
        ans += dx * dy;
    }
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A&lang=ja
