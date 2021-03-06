#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VD = vector<double>;
using VVD = vector<VD>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


// Reference: <http://cslabcms.nju.edu.cn/problem_solving/images/0/06/2-Bitonic-%E8%82%96%E6%B1%9F.pdf>
//   --> 疑似コードにミスが多いので注意

struct Point { double x, y; };
using Points = vector<Point>;
double dist(Point& a, Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

// TODO: verify the "path"
pair<double, VLL> bitonic_tsp(ll N, Points& P) {
    if (N == 2) { return make_pair(2*dist(P[1],P[2]), VLL{2, 1}); }
    // if (N == 2) { return make_pair(2*dist(P[1],P[2]), VLL{1, 2}); }

    // dp[i][j] := P1 <- Pi と左方向に進み P1 -> Pj と右方向に進む時の最短距離
    //  R[i][j] := dp[i][j] において P1 -> Pj と右方向に進む時の Pj の直前の点
    //  (i < j)
    VVD dp(N+1, VD(N+1, INF)); dp[1][2] = dist(P[1], P[2]);
    VVLL R(N+1, VLL(N+1,-1)); R[1][2] = 0;
    FOR(j,3,N+1) {
        FOR(i,1,(j-2)+1) {  // i < j-1
            dp[i][j] = dp[i][j-1] + dist(P[j-1],P[j]);
            R[i][j] = j - 1;
        }
        FOR(k,1,(j-2)+1) {  // i = j-1
            if (chmin(dp[j-1][j], dp[k][j-1] + dist(P[k],P[j]))) {
                R[j-1][j] = k;
            }
        }
    }
    dp[N][N] = dp[N-1][N] + dist(P[N-1],P[N]);

    VLL path;  // PN を出発点とした時の最短経路パス
    path.push_back(N);
    path.push_back(N-1);
    auto rec = [&](auto self, ll i, ll j) -> void {
        if (i < j) {
            ll k = R[i][j];
            if (k == 0) return;
            path.push_back(k);
            self(self, i, k);
        } else {
            ll k = R[j][i];
            if (k == 0) return;
            self(self, k, j);
            path.push_back(k);
        }
    };
    rec(rec, R[N-1][N], N-1);
    path.push_back(R[N-1][N]);
    return make_pair(dp[N][N], path);

    /**
    // P1 を出発点とした時の最短経路パスに修正
    VLL path2(N);
    ll idx_1 = -1, k = 0;
    REP(i,N) if (path[i] == 1) { idx_1 = i; break; }
    FOR(i,idx_1,N) path2[k++] = path[i];
    FOR(i,0,idx_1) path2[k++] = path[i];
    return make_pair(dp[N][N], path2);
    **/
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    Points P(N+1); FOR(i,1,N+1) cin >> P[i].x >> P[i].y;

    double ans;
    VLL path;
    tie(ans, path) = bitonic_tsp(N, P);
    cout << ans << endl;

    // for (ll p : path) cout << p << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_2_C&lang=ja
