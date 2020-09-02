#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;



// https://atcoder.jp/contests/abc128/tasks/abc128_c
int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> s(M);
    int k, t;
    rep(i, M) {
        cin >> k;
        rep(j, k) {
            cin >> t;
            s[i].push_back(t - 1);
        }
    }
    vector<int> p(M);
    rep(i, M) cin >> p[i];

    int ans = 0;
    for (int bit = 0; bit < (1 << N); bit++) {
        bool are_light = true;
        for (int i = 0; i < M; i++) {
            int count = 0;
            for (auto ss : s[i]) {
                if (bit & (1 << ss)) count++;
            }
            if (count % 2 != p[i]) are_light = false;
        }
        if (are_light) ans++;
    }
    cout << ans << endl;
    return 0;
}