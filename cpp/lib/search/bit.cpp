#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) ((b>>i) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M; cin >> N >> M;
    VVLL s(M);
    REP(i,M) {
        ll k; cin >> k;
        REP(j,k) {
            ll t; cin >> t;
            s[i].push_back(t-1);
        }
    }
    VLL p(M); REP(i,M) cin >> p[i];

    ll ans = 0;
    REP(S,1<<N) {
        bool are_light = true;
        REP(i,M) {
            ll count = 0;
            for (auto& ss : s[i]) if (BIT(S,ss)) count++;
            if (count % 2 != p[i]) are_light = false;
        }
        if (are_light) ans++;
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/abc128/tasks/abc128_c
