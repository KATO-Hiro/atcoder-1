#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


int main() {
    const ll MOD = 1e+9 + 7;
    int N;
    cin >> N;
    vector<ll> A(N);
    rep(i, N) cin >> A[i];

    vector<ll> S(N + 1, 0);
    rep(i, N) {
        S[i + 1] += S[i] + A[i];
        S[i + 1] %= MOD;
    }

    ll ans = 0;
    rep(i, N) {
        ans += S[i] * A[i];
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}