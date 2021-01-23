#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
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
#define SZ(c) ((ll)(c).size())
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << #x << " = " << (x) << '\n';
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VVVLL = vector<VVLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VVVB = vector<VVB>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
// static const int INF = (1 << 30) - 1;  // 1073741824 - 1
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL X(N),Y(N); REP(i,N) cin >> X[i] >> Y[i];

    ll M; cin >> M;
    VP OP(M);
    REP(i,M) {
        ll q; cin >> q;
        if (q <= 2) {
            OP[i] = P(q, -1);
        } else {
            ll p; cin >> p;
            OP[i] = P(q, p);
        }
    }

    ll Q; cin >> Q;
    vector<tuple<ll,ll,ll>> AB(Q);
    REP(i,Q) {
        ll A, B; cin >> A >> B;
        B--;
        AB[i] = {A, B, i};
    }

    auto mat_mul = [&](VVLL& A, VVLL& B) -> VVLL {
        const ll n1 = (ll)A.size();
        const ll n2 = (ll)B.size();  // = A[0].size()
        const ll n3 = (ll)B[0].size();
        VVLL C(n1, VLL(n3, 0));
        REP(i,n1) REP(k,n2) REP(j,n3) {
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]);
        }
        return C;
    };

    VVLL A = {{1, 0, 0},
              {0, 1, 0},
              {0, 0, 1}};
    VVLL A1 = {{0, 1, 0},
               {-1,0, 0},
               {0, 0, 1}};
    VVLL A2 = {{0,-1, 0},
               {1, 0, 0},
               {0, 0, 1}};
    VVLL TX = {{1, 0, 0},
               {0, 1, 0},
               {0, 0, 1}};
    VVLL RX = {{1, 0, 0},
               {0,-1, 0},
               {0, 0, 1}};
    VVLL RY = {{-1,0, 0},
               {0, 1, 0},
               {0, 0, 1}};

    SORT(AB);
    VVLL ans(Q, VLL(2));
    ll x = 0;
    ll q, p;
    REP(i,M+1) {
        while (x < Q) {
            ll a, b, id;
            tie(a, b, id) = AB[x];
            if (a == i) {
                x++;
                ans[id][0] = A[0][0] * X[b] + A[0][1] * Y[b] + A[0][2] * 1;
                ans[id][1] = A[1][0] * X[b] + A[1][1] * Y[b] + A[1][2] * 1;
            } else {
                break;
            }
        }
        if (x == Q) break;
        if (i == M) break;

        // REP(i,3) REP(j,3) debug(A[i][j])

        tie(q, p) = OP[i];
        if (q == 1) {
            A = mat_mul(A1, A);
        } else if (q == 2) {
            A = mat_mul(A2, A);
        } else if (q == 3) {
            TX[0][2] = -p;
            TX[1][2] = 0;
            A = mat_mul(TX, A);
            A = mat_mul(RY, A);
            TX[0][2] = p;
            TX[1][2] = 0;
            A = mat_mul(TX, A);
        } else {
            TX[0][2] = 0;
            TX[1][2] = -p;
            A = mat_mul(TX, A);
            A = mat_mul(RX, A);
            TX[0][2] = 0;
            TX[1][2] = p;
            A = mat_mul(TX, A);
        }

        // REP(i,3) REP(j,3) debug(A[i][j])
        // return 0;

    }

    REP(i,Q) {
        cout << ans[i][0] << " " << ans[i][1] << '\n';
    }

    return 0;
}
