#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


int main() {
    string S, T;
    cin >> S >> T;

    int N = S.size();
    int M = T.size();

    int ans = 1 << 30;
    for (int i = 0; i <= N - M; i++) {
        int diff = 0;
        rep(j, M) if (S[i + j] != T[j]) diff++;
        ans = min(ans, diff);
    }
    cout << ans << endl;

    return 0;
}