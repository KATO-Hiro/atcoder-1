#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


int main() {
    int D, T, S;
    cin >> D >> T >> S;

    string ans;
    if (((double)D / S) <= T) ans = "Yes";
    else ans = "No";
    cout << ans << endl;
    return 0;
}