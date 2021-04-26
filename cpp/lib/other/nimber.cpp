#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;

    // nimber (grundy number)
    VLL nim(N+1); nim[1] = 0;
    FOR(i,2,N+1) {
        unordered_set<ll> S;
        if (i % 2 == 0) { S.insert(nim[i/2] ^ nim[i/2]); }
        if (i % 2 == 1) { S.insert(nim[i/2] ^ nim[i/2 + 1]); }
        if (i % 3 == 0) { S.insert(nim[i/3] ^ nim[i/3] ^ nim[i/3]); }
        if (i % 3 == 1) { S.insert(nim[i/3] ^ nim[i/3] ^ nim[i/3 + 1]); }
        if (i % 3 == 2) { S.insert(nim[i/3] ^ nim[i/3 + 1] ^ nim[i/3 + 1]); }

        ll g = 0;
        while (S.count(g) != 0) g++;
        nim[i] = g;
    }

    string ans = (nim[N] != 0 ? "A" : "B");
    cout << ans << endl;

    return 0;
}
// Verify: https://yukicoder.me/problems/no/153
