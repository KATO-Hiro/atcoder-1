#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
// --------------------------------------------------------


bool is_palindrome(string& S) {
    ll N = (ll)S.size();
    for (ll i = 0; i <= N/2; i++) {
        if (S[i] != S[N-1 - i]) return false;
    }
    return true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    string ans = (is_palindrome(S) ? "YES" : "NO");
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/arc031/tasks/arc031_1
