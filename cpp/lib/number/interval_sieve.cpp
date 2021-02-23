#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------

/**
 * @brief エラトステネスの区間篩
 *        区間 [L, R] における素数を求める
 * @param L 区間下限
 * @param R 区間上限
 * @return vector<bool> res[x-L] = true ⇔ x が素数
 */
vector<bool> interval_seive(ll L, ll R) {
    assert(!(L == 0 && R == 0));
    assert(L <= R);
    ll root_R = (ll)(sqrt(R) + 0.5);
    vector<bool> prime_1(root_R+1, true);
    vector<bool> prime_2(R-L+1, true);
    if (L == 0) prime_2[0] = prime_2[1] = false;
    if (L == 1) prime_2[0] = false;
    // 2
    for (ll j = 2*2; j <= root_R; j += 2) prime_1[j] = false;
    for (ll j = max(2LL,(L+2-1)/2)*2; j <= R; j += 2) prime_2[j-L] = false;
    // 3, 5, 7, ...
    for (ll i = 3; i <= root_R; i += 2) {
        if (!prime_1[i]) continue;
        for (ll j = 2*i; j <= root_R; j += i) prime_1[j] = false;
        for (ll j = max(2LL,(L+i-1)/i)*i; j <= R; j += i) prime_2[j-L] = false;
    }
    return prime_2;
}


// TODO: Verify
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll L, R; cin >> L >> R;

    auto is_prime = interval_seive(L, R);
    for (ll i = L; i <= R; i++) {
        cout << i << ": " << is_prime[i-L] << endl;
    }

    return 0;
}
