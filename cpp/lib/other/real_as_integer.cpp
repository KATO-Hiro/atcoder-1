#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------


// 実数値を d 倍した整数として扱い誤差なく処理する構造体
struct RealAsInteger {
    ll d;  // 実数値を整数値に変換するための係数  e.g.) 1000
    RealAsInteger(const ll& _d) { d = _d; };

    // 実数値の入力を受け取り d 倍した整数に変換する
    // 小数点以下を繰り上げても正確に整数ではない場合があるため round で丸める
    // e.g.) 入力が 1.234 の場合
    //   RealAsInteger real(d=1000);
    //   ll x = real.input();  // x = 1234
    ll input() { long double x; cin >> x; return llround(x * d); }

    // x 以上の最小の整数
    ll ceil(const ll& x)  { return d * ( (x < 0) ? x / d : (x + d - 1) / d ); }

    // x 以下の最大の整数
    ll floor(const ll& x) { return d * ( (x > 0) ? x / d : (x - d + 1) / d ); }

};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    static const ll d = 10000;
    RealAsInteger real(d);

    ll X = real.input();
    ll Y = real.input();
    ll R = real.input();

    ll y1 = real.ceil(Y - R);   // 下端
    ll y2 = real.floor(Y + R);  // 上端

    // root (root^2 = root2) 以下の最大の実数 (d 倍した整数) を返す
    auto f = [&](ll root2) -> ll {
        ll ok = 0;
        ll ng = 2e9;
        ll mid;
        while (ng - ok > 1) {
            mid = (ok + ng) / 2;
            bool is_ok = mid*mid <= root2;
            (is_ok ? ok : ng) = mid;
        }
        return ok;
    };

    ll ans = 0;
    for (ll y = y1; y <= y2; y += d) {
        ll dx = f(R*R - (Y-y)*(Y-y));
        ll x1 = real.ceil(X - dx);
        ll x2 = real.floor(X + dx);
        ans += (x2 - x1) / d + 1;
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc191/tasks/abc191_d
