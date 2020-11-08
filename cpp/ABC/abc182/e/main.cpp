#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define MIN(c) *min_element(ALL(c))
#define MAX(c) *max_element(ALL(c))
#define SUM(c) accumulate(ALL(c), 0)
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((int)(c).size())
#define debug(x) cerr << #x << " = " << (x) << '\n';
using P = pair<int,int>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VD = vector<double>;
using VVD = vector<VD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
static const int INF = (1 << 30) - 1;  // 1073741824 - 1
// static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;

struct light {
    int h, w, d;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int H, W; cin >> H >> W;
    int N, M; cin >> N >> M;

    VVI S(H+2, VI(W+2, 0));
    VVI X(W+2, {0,H+1}), Y(H+2, {0,W+1});
    REP(i,N) {
        int A, B; cin >> A >> B;
        S[A][B] = 1;
        Y[A].push_back(B);
        X[B].push_back(A);
    }
    REP(i,M) {
        int C, D; cin >> C >> D;
        S[C][D] = -1;
        Y[C].push_back(D);
        X[D].push_back(C);
    }

    FOR(h,1,H+1) SORT(Y[h]);
    FOR(w,1,W+1) SORT(X[w]);

    int ans = N;
    FOR(h,1,H+1) FOR(w,1,W+1) {
        if (S[h][w] != 0) continue;
        auto it_w = lower_bound(ALL(Y[h]), w);
        int w_r = *it_w;
        int w_l = *(it_w - 1);
        if (S[h][w_r] == 1 || S[h][w_l] == 1) {
            ans++;
            continue;
        }
        auto it_h = lower_bound(ALL(X[w]), h);
        int h_r = *it_h;
        int h_l = *(it_h - 1);
        if (S[h_l][w] == 1 || S[h_r][w] == 1) {
            ans++;
        }
    }
    cout << ans << '\n';

    return 0;
}
