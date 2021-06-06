#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
static const double EPS = 1e-10;
// --------------------------------------------------------

// References:
//   <https://en.wikipedia.org/wiki/Ternary_search>
//   <https://kyopro.hateblo.jp/entry/2019/04/25/134128>
//   <https://nodchip.hatenadiary.org/entry/20090303/1236058357>
//     -> ループ回数固定推奨の話
//   <https://twitter.com/noshi91/status/1261924911448129538>
//     -> 三分探索で極小が求まらないやつ

/** NOTE: 三分探索は "単峰性関数" の最小/最大を求めるアルゴリズム
          -> 関数を描画して三分探索が使えるか確認
             <https://www.geogebra.org/graphing?lang=ja>
**/

double ternary_search() {
    auto f = [](double x) -> double {
        /** TODO: 関数を実装する **/
    };

    /** TODO: 問題に合わせて適切に設定する **/
    double l = 1.23;
    double r = 4.56;
    while (abs(r - l) > EPS) {
        double m1 = (2*l + r) / 3;
        double m2 = (l + 2*r) / 3;
        /** NOTE: 極大値を求める場合は不等号を逆にする **/
        if (f(m1) < f(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return (l + r) / 2;
}


ll ternary_search_integer() {
    auto f = [](ll x) -> ll {
        /** TODO: 関数を実装する **/
    };

    /** TODO: 問題に合わせて適切に設定する **/
    ll l = 123;
    ll r = 456;
    while (r - l > 2) {
        ll m1 = (2*l + r) / 3;
        ll m2 = (l + 2*r) / 3;
        /** NOTE: 極大値を求める場合は不等号を逆にする **/
        if (f(m1) < f(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return (l + r) / 2;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    double P; cin >> P;

    auto f = [&](double x) -> double {
        return x + P / (pow(2, x / 1.5));
    };

    double l = 0.0;
    double r = P;
    while (abs(r - l) > EPS) {
        double m1 = (2*l + r) / 3;
        double m2 = (l + 2*r) / 3;
        if (f(m1) < f(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    double m = (l + r) / 2;
    double ans = f(m);
    cout << ans << endl;

    return 0;
}
// verify: https://atcoder.jp/contests/arc054/tasks/arc054_b
