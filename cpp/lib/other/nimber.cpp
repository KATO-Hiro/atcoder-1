#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL W(N); REP(i,N) cin >> W[i];
    VLL B(N); REP(i,N) cin >> B[i];

    const ll WW = 50;
    const ll BB = 1325;  // (1+2+..+50) + 50
    const ll M  = 1375;  // max nimber (= WW + BB)

    // nimber (grundy number)
    // 今の状態から一手で行ける状態の nimber に含まれていない最小の非負整数
    VVLL nim(WW+1,VLL(BB+1,-1));
    nim[0][0] = nim[0][1] = 0;
    auto rec = [&](auto self, ll w, ll b) -> ll {
        if (nim[w][b] != -1) return nim[w][b];

        VB mex(M,false);
        if (w >= 1) mex[self(self, w-1, b+w)] = true;
        FOR(k,1,b/2+1) mex[self(self, w, b-k)] = true;

        REP(i,M) if (!mex[i]) return nim[w][b] = i;
        return -1;
    };

    ll nimber = 0;
    REP(i,N) nimber ^= rec(rec, W[i], B[i]);
    string ans = (nimber != 0 ? "First" : "Second");
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/typical90/tasks/typical90_ae
