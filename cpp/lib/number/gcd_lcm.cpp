#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


ll gcd(ll a, ll b) {
    if (b == 0) return a;
    ll r = a % b;
    return gcd(b, r);
}


ll lcm(ll a, ll b) {
    return (a * b) / gcd(a, b);
}


// Verify: https://onlinejudge.u-aizu.ac.jp/challenges/search/categories/0005
int main() {
    string s;
    int idx;
    ll a, b, gcd_, lcm_;
    while (getline(cin, s)) {
        idx = s.find(" ");
        a = stoi(s.substr(0, idx));
        b = stoi(s.substr(idx + 1));

        gcd_ = gcd(a, b);
        lcm_ = lcm(a, b);
        cout << gcd_ << " " << lcm_ << endl;
    }
    return 0;
}
