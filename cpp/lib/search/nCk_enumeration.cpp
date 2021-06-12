#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) (((b)>>(i)) & 1)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
// --------------------------------------------------------


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, K; cin >> N >> K;

    // 組み合わせの列挙 (nCk)
    ll comb = (1<<K) - 1;
    while (comb < (1<<N)) {
        cout << comb << ":";
        REP(i,N) if (BIT(comb,i)) cout << " " << i;
        cout << '\n';

        // 更新処理
        ll x = comb & (-comb);
        ll y = comb + x;
        ll z = comb & ~y;
        comb = ((z/x) >> 1) | y;
    }

    return 0;
}

// verify: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_11_D&lang=ja
