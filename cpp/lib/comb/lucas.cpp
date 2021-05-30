#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------

// References:
//   <https://manabitimes.jp/math/1324>
//   <https://algo-logic.info/binomial-coefficient-lucas/>

/**
 * @brief Lucas の定理を用いて nCk mod p を計算する (p は素数)
 *        - 前計算: O(p^2)
 *        - クエリ: O(log_p(n))
 */
struct Lucas {
    int p;
    vector<vector<int>> com;  // 二項係数 (p 進表記用)
    Lucas() {}
    Lucas(int p_) : p(p_) {
        com.assign(p, vector<int>(p,0));
        com[0][0] = 1;
        for (int i = 1; i < p; i++) {
            com[i][0] = com[i][i] = 1;
            for (int j = 1; j < i; j++) {
                com[i][j] = (com[i-1][j] + com[i-1][j-1]) % p;
            }
        }
    }

    // nCk mod p を求める
    //   - O(log_p(n))
    //   - nCk = Π niCki (mod p)
    int C(int n, int k) {
        if (n < k) return 0;
        int res = 1;
        while (n > 0) {
            int ni = n % p;
            int ki = k % p;
            (res *= com[ni][ki]) %= p;
            n /= p;
            k /= p;
        }
        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    string S; cin >> S;

    const ll p = 3;
    Lucas lc(p);

    // (R,B,W) = (0,1,2)
    ll total = 0;
    REP(i,N) {
        if (S[i] == 'R') total += 0 * lc.C(N-1,i);
        if (S[i] == 'B') total += 1 * lc.C(N-1,i);
        if (S[i] == 'W') total += 2 * lc.C(N-1,i);
        total %= p;
    }
    if ((N-1) % 2 == 1) total = (p - total) % p; 

    if (total == 0) cout << "R" << endl;
    if (total == 1) cout << "B" << endl;
    if (total == 2) cout << "W" << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/arc117/tasks/arc117_c
