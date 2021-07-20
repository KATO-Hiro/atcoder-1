#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SZ(c) ((ll)(c).size())
using VLL = vector<ll>;
using VB = vector<bool>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, X, M; cin >> N >> X >> M;

    VLL A = {X};
    auto f = [&](ll n) -> ll { return (A[n] * A[n]) % M; };

    // 助走区間 --> ループ
    // -->-->--v
    //      |  |
    //      ^--<
    // 0 -> 1 -> ... -> loop_s -> ... -> SZ(A) - 1 -> loop_s
    VB used(M,false); used[X] = true;
    ll loop_s = -1;
    while (true) {
        ll a = f(SZ(A) - 1);
        if (used[a]) { loop_s = find(ALL(A), a) - A.begin(); break; }
        used[a] = true;
        A.push_back(a);
    }
    ll loop_len = SZ(A) - loop_s;
 
    ll ans = 0;
    if (N <= loop_s) {
        REP(i,N) ans += A[i];
    } else {
        ll q = (N - loop_s) / loop_len;
        ll r = (N - loop_s) % loop_len;
        ll sum = 0; FOR(i,loop_s,SZ(A)) sum += A[i];

        REP(i,loop_s) ans += A[i];
        ans += sum * q;
        FOR(i,loop_s,loop_s + r) ans += A[i];
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc179/tasks/abc179_e
