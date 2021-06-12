#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    ll K; cin >> K;
    VLL B(K); REP(i,K) cin >> B[i];

    ll S = 0;
    for (ll b : B) S |= (1<<b);

    // 集合 S の部分集合 T の列挙
    //   e.g.)
    //     S = 0101
    //     T = 0101 (= S)
    //         0100
    //         0001
    //         0000 (= 0)

    VVLL ans;
    for (ll T = S; 0 <= T; T--) {
        T &= S;
        /** NOTE: 問題に合わせて切り替える **/
        // if (T == S) continue;
        // if (T == 0) continue;

        VLL X = {T};
        REP(i,N) if (BIT(T,i)) X.push_back(i);
        ans.push_back(X);
    }

    RREP(i,SZ(ans)) {
        auto& Y = ans[i];
        cout << Y[0] << ":";
        FOR(i,1,SZ(Y)) cout << " " << Y[i];
        cout << '\n';
    }

    return 0;
}
// verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_11_C&lang=ja
