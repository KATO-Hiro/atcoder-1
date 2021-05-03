#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define BIT(b,i) (((b)>>(i)) & 1)
using VS = vector<string>;
// --------------------------------------------------------


// 括弧列の判定
bool is_parentheses_column(const string& S) {
    const ll N = (ll)S.size();
    ll pos = 0;
    REP(i,N) {
        if (S[i] == '(') pos++;
        if (S[i] == ')') pos--;
        if (pos < 0) return false;
    }
    return pos == 0;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;

    VS ans;
    REP(S,1<<N) {
        string T = "";  // 001011 = (()())
        RREP(i,N) T += (!BIT(S,i) ? '(' : ')');
        if (is_parentheses_column(T)) ans.push_back(T);
    }
    for (string& a : ans) cout << a << '\n';

    return 0;
}
// Verify: https://atcoder.jp/contests/typical90/tasks/typical90_b
