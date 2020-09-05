#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


int binary_search(vector<int> &a, int key) {
    // Meguru type binary search
    int ok = -1;
    int ng = a.size();

    auto is_ok = [&] (int idx) {
        if (a[idx] < key) {
            return true;
        } else {
            return false;
        }
    };

    int mid;
    while (abs(ok - ng) > 1) {
        mid = (ok + ng) / 2;
        if (is_ok(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}


// Verify: https://atcoder.jp/contests/abc143/tasks/abc143_d
int main() {
    int N;
    cin >> N;
    vector<int> L(N);
    rep(i, N) cin >> L[i];

    sort(L.begin(), L.end());

    ll ans = 0;
    for (int a = 0; a < N - 2; a++) {
        for (int b = a + 1; b < N - 1; b++) {
            // c < a + b
            int c = binary_search(L, L[a] + L[b]);
            ans += c - b;
        }
    }
    cout << ans << endl;
    return 0;
}