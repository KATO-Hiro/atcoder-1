#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


// 愚直な二項係数の計算 : O(N^2)
// NOTE: MOD を取りたい場合は Lucas (MOD∈素数) を使うか modint の comb を使う
VVLL combination_pascal(ll N) {
    VVLL C(N+1,VLL(N+1,0));
    C[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
    return C;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll A, B, K; cin >> A >> B >> K;

    ll N = A + B;
    auto C = combination_pascal(N);

    ll pos = 0;
    ll a = A, b = B, n = N;
    string ans = "";
    REP(_,N) {
        if (a == 0) { ans += string(b, 'b'); break; }
        if (b == 0) { ans += string(a, 'a'); break; }

        if (K <= pos + C[n-1][a-1]) {
            ans += 'a'; a--;
        } else {
            ans += 'b'; b--;
            pos += C[n-1][a-1];
        }
        n--;
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc202/tasks/abc202_d
