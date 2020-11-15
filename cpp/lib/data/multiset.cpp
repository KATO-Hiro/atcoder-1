#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define SZ(c) ((int)(c).size())
using VI = vector<int>;
// --------------------------------------------------------


// https://atcoder.jp/contests/abc170/tasks/abc170_e

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N, Q; cin >> N >> Q;
    int M = 200000;
    VI A(N+1),B(N+1); FOR(i,1,N+1) cin >> A[i] >> B[i];
    VI C(Q+1),D(Q+1); FOR(i,1,Q+1) cin >> C[i] >> D[i];

    vector<multiset<int>> Y(M+1);
    FOR(i,1,N+1) {
        Y[B[i]].insert(A[i]);
    }
    multiset<int> F;
    FOR(i,1,M+1) {
        if (SZ(Y[i]) > 0) {
            F.insert(*Y[i].rbegin());
        }
    }

    int y1, y2, r;
    FOR(i,1,Q+1) {
        r = A[C[i]];
        y1 = B[C[i]];
        y2 = D[i];

        // 転園元/転園先の幼稚園の最大レートを削除
        F.erase(F.find(*Y[y1].rbegin()));
        if (SZ(Y[y2]) > 0) F.erase(F.find(*Y[y2].rbegin()));

        // 転園
        Y[y1].erase(Y[y1].find(r));
        Y[y2].insert(r);
        B[C[i]] = y2;

        // 転園元/転園先の幼稚園の最大レートを追加
        if (SZ(Y[y1]) > 0) F.insert(*Y[y1].rbegin());
        F.insert(*Y[y2].rbegin());

        // 最小レート
        cout << *F.begin() << '\n';
    }

    return 0;
}
