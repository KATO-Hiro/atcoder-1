#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------
#include <atcoder/math>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;

    ll ans = 2*N-1;
    ll root = floorl(sqrtl(2*N) + 0.5);
    FOR(d1,2,root+1) if (2*N % d1 == 0) {
        ll d2 = 2*N / d1;

        // k   ≡ 0 (mod m1)
        // k+1 ≡ 0 (mod m2)
        auto f = [&](ll m1, ll m2) -> void {
            auto [y, z] = crt({0, m2-1}, {m1, m2});
            if (z != 0) chmin(ans, y);
        };
        f(d1, d2);
        f(d2, d1);
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/acl1/tasks/acl1_b
