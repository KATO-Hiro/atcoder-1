#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


// Verify: https://atcoder.jp/contests/abc150/tasks/abc150_c
int main() {
    int N;
    cin >> N;
    vector<int> P(N), Q(N);
    rep(i, N) cin >> P[i];
    rep(i, N) cin >> Q[i];

    vector<int> R(N);
    iota(R.begin(), R.end(), 1);  // 1, 2, 3, ... , N

    int a, b, i = 1;
    do {
        if (equal(P.begin(), P.end(), R.begin(), R.end())) a = i;
        if (equal(Q.begin(), Q.end(), R.begin(), R.end())) b = i;
        i++;
    } while (next_permutation(R.begin(), R.end()));
    cout << abs(a - b) << endl;

    return 0;
}