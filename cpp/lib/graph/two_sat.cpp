#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define COUT(c) cout << (c) << '\n'
using VLL = vector<ll>;
// --------------------------------------------------------
#include <atcoder/twosat>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, D; cin >> N >> D;
    VLL X(N),Y(N); REP(i,N) cin >> X[i] >> Y[i];

    two_sat ts(N);
    REP(i,N) REP(j,N) if (i != j) {
        // (x_i = f) ∨ (x_j = g) というクローズを足す
        //   e.g.) ts.add_clause(i,true,j,true)
        //         -> (x_i = true) または (x_j = true) が成立する必要あり
        if (llabs(X[i] - X[j]) < D) ts.add_clause(i,false,j,false);
        if (llabs(X[i] - Y[j]) < D) ts.add_clause(i,false,j,true);
        if (llabs(Y[i] - X[j]) < D) ts.add_clause(i,true, j,false);
        if (llabs(Y[i] - Y[j]) < D) ts.add_clause(i,true, j,true);
    }

    if (ts.satisfiable()) {
        COUT("Yes");
        auto B = ts.answer();
        REP(i,N) COUT(B[i] ? X[i] : Y[i]);
    } else {
        COUT("No");
    }

    return 0;
}
// Verify: https://atcoder.jp/contests/practice2/tasks/practice2_h
