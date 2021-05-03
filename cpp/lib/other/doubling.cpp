#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, T; cin >> N >> T;
    VLL A(N+1); FOR(i,1,N+1) cin >> A[i];

    // 二進表記で T を表現するために必要な桁数
    ll K = 1; while ((1LL << K) <= T) K++;

    // db[k][i] := 町 i からテレポーターを 2^k 回使ったとき到着する町
    VVLL db(K, VLL(N+1));
    FOR(i,1,N+1) db[0][i] = A[i];
    FOR(k,1,K) FOR(i,1,N+1) {
        db[k][i] = db[k-1][db[k-1][i]];
    }

    ll pos = 1;
    REP(k,K) if (BIT(T,k)) {
        pos = db[k][pos];
    }
    cout << pos << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/abc167/tasks/abc167_d
