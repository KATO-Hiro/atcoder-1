#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using P = pair<int,int>;
using VP = vector<P>;
using VVP = vector<VP>;
using VI = vector<int>;
using VVI = vector<VI>;
const int INF = 1 << 30;
// --------------------------------------------------------


bool bellman_ford(int V, VVP &G, VI &d, int s) {
    d[s] = 0;
    int v, c;
    REP(i, V) REP(u, V) {
        if (d[u] == INF) continue;
        for (auto vc : G[u]) {
            tie(v, c) = vc;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                if (i == V - 1) return true;
            }
        }
    }
    return false;
}


// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int V, E, r; cin >> V >> E >> r;
    VVP G(V, VP());
    REP(_, E) {
        int s, t, d; cin >> s >> t >> d;
        G[s].push_back(make_pair(t, d));
    }

    VI d(V, INF);
    bool exist_negative_cycle = bellman_ford(V, G, d, r);
    if (exist_negative_cycle) {
        cout << "NEGATIVE CYCLE" << '\n';
    } else {
        REP(i, V) {
            if (d[i] == INF) {
                cout << "INF" << '\n';
            } else {
                cout << d[i] << '\n';
            }
        }
    }

    return 0;
}
