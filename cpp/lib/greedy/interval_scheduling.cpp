#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


// https://atcoder.jp/contests/keyence2020/tasks/keyence2020_b
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N; cin >> N;
    vector<vector<int>> A(N, vector<int>(2));
    int X, L;
    rep(i, N) {
        cin >> X >> L;
        A[i][0] = X - L;
        A[i][1] = X + L;
    }

    sort(A.begin(), A.end(), [](auto a, auto b) {return a[1] < b[1];});
    int ans = 0;
    int prev_end = -1e+9;
    rep(i, N) {
        if (prev_end <= A[i][0]) {
            prev_end = A[i][1];
            ans++;
        }
    }
    cout << ans << '\n';

    return 0;
}