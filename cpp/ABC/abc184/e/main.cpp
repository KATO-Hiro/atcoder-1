#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (int i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define MIN(c) *min_element(ALL(c))
#define MAX(c) *max_element(ALL(c))
#define SUM(c) accumulate(ALL(c), 0)
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((int)(c).size())
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int H, W; cin >> H >> W;
    VS S(H); REP(i,H) cin >> S[i];

    VVP A(26);
    VB B(26, false);
    int sh = -1, sw = -1, gh = -1, gw = -1;
    REP(h,H) REP(w,W) {
        if (S[h][w] == 'S') {
            sh = h; sw = w;
        } else if (S[h][w] == 'G') {
            gh = h; gw = w;
        } else if (islower(S[h][w])) {
            A[S[h][w] - 'a'].push_back(P(h, w));
        }
    }

    VVI d(H, VI(W, INF));
    d[sh][sw] = 0;
    queue<pair<P, bool>> q;
    q.push(pair(P(sh, sw),false));
    int h, w; bool b;
    VI dh = {0,0,1,-1};
    VI dw = {1,-1,0,0};
    while (!q.empty()) {
        auto x = q.front(); q.pop();
        tie(h, w) = x.first;
        b = x.second; 
        if (h == gh && w == gw) continue;
        if (islower(S[h][w]) && !b) {
            if (!B[S[h][w] - 'a']) {
                B[S[h][w] - 'a'] = true;
                for (P p : A[S[h][w] - 'a']) {
                    int hh = p.first;
                    int ww = p.second;
                    if (h == hh && w == ww) continue;
                    if (d[hh][ww] != INF) continue;
                    d[hh][ww] = d[h][w] + 1;
                    q.push(pair(P(hh, ww),true));
                }
            }
        }
        REP(i,4) {
            int hh = h + dh[i];
            int ww = w + dw[i];
            if (hh < 0 || H <= hh || ww < 0 || W <= ww) continue;
            if (S[hh][ww] == '#') continue;
            if (d[hh][ww] != INF) continue;
            d[hh][ww] = d[h][w] + 1;
            q.push(pair(P(hh, ww),false));
        }
    }

    int ans = (d[gh][gw] == INF) ? -1 : d[gh][gw];
    cout << ans << '\n';

    return 0;
}
