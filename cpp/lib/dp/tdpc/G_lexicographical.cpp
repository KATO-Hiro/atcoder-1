#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

// NOTE
//   - 部分列 DP
//   - 辞書順 + 復元
//   - オーバーフロー対処あり

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    ll K; cin >> K;
    ll N = (ll)S.size();

    // dp[i][c] := i 文字目以降で文字 c から始まる部分列の個数
    VVLL dp(N+1,VLL(26,0));
    RREP(i,N) REP(c,26) {
        if (c == S[i] - 'a') {
            dp[i][c] = 1;
            REP(cc,26) dp[i][c] = min(dp[i][c] + dp[i+1][cc], INF);
        } else {
            dp[i][c] = dp[i+1][c];
        }
    }

    ll tot = 0;
    REP(c,26) tot = min(tot + dp[0][c], INF);
    if (tot < K) { cout << "Eel" << endl; return 0; }

    // dp テーブルから復元
    string ans = "";
    [&]() -> void {
        ll k = 0;
        REP(i,N) REP(c,26) {
            if (k + dp[i][c] < K) {
                k += dp[i][c];
            } else {
                char cc = ('a' + c);  // 次の文字
                ans += cc;
                k++;  // cc 以降が空文字となる部分列をカウント
                if (k == K) return;
                while (cc != S[i]) i++;  // cc 出現位置まで移動して dp との整合性を保つ
                break;
            }
        }
    }();
    cout << ans << endl;

    return 0;
}
// https://atcoder.jp/contests/tdpc/tasks/tdpc_lexicographical
