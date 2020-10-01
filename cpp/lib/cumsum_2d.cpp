#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VI = vector<int>;
using VVI = vector<VI>;
// --------------------------------------------------------


// Verify: https://atcoder.jp/contests/joi2011ho/tasks/joi2011ho1
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int H, W; cin >> H >> W;
    int K; cin >> K;
    VVI J(H+1,VI(W+1,0)), O(H+1,VI(W+1,0)), I(H+1,VI(W+1,0));
    REP(h,H) {
        string S; cin >> S;
        REP(w,W) {
            if (S[w] == 'J') {
                J[h+1][w+1] = 1;
            } else if (S[w] == 'O') {
                O[h+1][w+1] = 1;
            } else {
                I[h+1][w+1] = 1;
            }
        }
    }
    // 2d cumsum
    FOR(h,1,H+1) FOR(w,1,W+1) {
        J[h][w] += J[h][w-1];
        O[h][w] += O[h][w-1];
        I[h][w] += I[h][w-1];
    }
    FOR(w,1,W+1) FOR(h,1,H+1) {
        J[h][w] += J[h-1][w];
        O[h][w] += O[h-1][w];
        I[h][w] += I[h-1][w];
    }

    REP(_, K) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << (J[c][d] - J[a-1][d] - J[c][b-1] + J[a-1][b-1]) << " ";
        cout << (O[c][d] - O[a-1][d] - O[c][b-1] + O[a-1][b-1]) << " ";
        cout << (I[c][d] - I[a-1][d] - I[c][b-1] + I[a-1][b-1]) << '\n';
    }

    return 0;
}
