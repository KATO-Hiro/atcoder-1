#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
using VI = vector<int>;
using VVI = vector<VI>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, K; cin >> N >> K;
    VI A(N+1); FOR(i,1,N+1) cin >> A[i];

    int D = 1;  // 二進数表記で K を表現するために必要な桁数
    while ((1LL << D) <= K) D++;

    VVI db(D, VI(N+1));
    FOR(i,1,N+1) db[0][i] = A[i];

    FOR(k,1,D) FOR(i,1,N+1) {
        db[k][i] = db[k-1][db[k-1][i]];
    }

    int pos = 1;
    FOR(k,0,D) {
        if (K & (1LL << k)) {
            pos = db[k][pos];
        }
    }
    cout << pos << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/abc167/tasks/abc167_d
