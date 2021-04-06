#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


// 文字列 S における長さ K の部分文字列のうち辞書順最小を求める
// ※ 部分文字列は連続しなくて良い (飛び飛びでも部分文字列とみなす)
string lexicographic_order_length_K(const string& S, ll K) {
    const ll N = (ll)S.size();
    assert(1 <= K && K <= N);

    string res(K,' ');
    ll k = 0;
    deque<char> d;
    REP(i,N) {
        while (!d.empty() && d.back() > S[i]) d.pop_back();
        d.push_back(S[i]);
        if (N - K <= i) {
            res[k++] = d.front(); d.pop_front();
        }
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    ll K; cin >> K;

    string ans = lexicographic_order_length_K(S, K);
    cout << ans << endl;

    return 0;
}
// Simple Verify: https://github.com/E869120/kyopro_educational_90/blob/main/sample/006.txt
