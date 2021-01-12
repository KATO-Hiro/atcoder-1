#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<ll,ll>;
using VLL = vector<ll>;
// --------------------------------------------------------


// ヒストグラムにおける最大長方形の面積を求める
//   - 配列の最後に番兵として 0 が必要
ll largest_rectangle_in_histogram(const VLL& H) {
    const ll N = (ll)H.size();
    stack<P> S;  // (l, h)
    ll res = 0;
    ll l, h;
    REP(r,N) {
        l = r;
        while (!S.empty() && S.top().second >= H[r]) {
            tie(l, h) = S.top(); S.pop();
            chmax(res, (r - l) * h);
        }
        S.push(P(l, H[r]));
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL H(N+1,0); REP(i,N) cin >> H[i];

    ll ans = largest_rectangle_in_histogram(H);
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C&lang=ja
