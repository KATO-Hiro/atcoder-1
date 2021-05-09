#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
using P = pair<ll,ll>;
using VP = vector<P>;
// --------------------------------------------------------

using ld = long double;

// NOTE: 3 頂点のなす角 ∠ABC は 0 ≦ θ ≦ π で考えるべきであるため，
//       計算都合で π を越えた場合は (2π - θ) とする必要あり
//         e.g.) 鋭角・鈍角の判定

// TODO: 厳密には long double でも誤差の問題はある
//       外積で誤差なく処理する方法があるらしい (AtCoder で必要になるかは微妙)

// 偏角ソート: 座標を偏角で昇順ソート．偏角の取りうる値の範囲は (-π,π] (∵ atan2)
// Reference: <https://qiita.com/ganariya/items/adef1a7f89ae88b804da>
void arg_sort(VP& points) {
    auto comp = [](const P& p1, const P& p2) -> bool {
        auto [x1, y1] = p1;
        auto [x2, y2] = p2;
        return atan2l(y1, x1) < atan2l(y2, x2);
    };
    sort(ALL(points), comp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VP points(N); REP(i,N) cin >> points[i].first >> points[i].second;

    arg_sort(points);

    ld ans = 0;
    REP(l,N) {
        ld x = 0, y = 0;
        FOR(r,l,l+N) {
            x += points[r % N].first;
            y += points[r % N].second;
            chmax(ans, sqrt(x*x + y*y));
        }
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc139/tasks/abc139_f