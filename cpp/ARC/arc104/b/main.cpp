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
static const int INF = 1 << 30;  // 1073741824
// static const ll INF = 1LL << 62;  // 4611686018427387904
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


static const int MAX_N = 5000;
VVI dp(MAX_N, VI(MAX_N, 0));

bool is_ok (char a, char b) {
    if (a == 'A' && b == 'T') return true;
    if (a == 'T' && b == 'A') return true;
    if (a == 'C' && b == 'G') return true;
    if (a == 'G' && b == 'C') return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N; cin >> N;
    string S; cin >> S;

    VI A(N+1,0), T(N+1,0), C(N+1,0), G(N+1,0);
    REP(i,N) {
        if (S[i] == 'A') {
            A[i+1]++;
        } else if (S[i] == 'T') {
            T[i+1]++;
        } else if (S[i] == 'C') {
            G[i+1]++;
        } else if (S[i] == 'G') {
            C[i+1]++;
        }
    }
    REP(i,N) {
        A[i+1] += A[i];
        T[i+1] += T[i];
        C[i+1] += C[i];
        G[i+1] += G[i];
    }

    int ans = 0;
    for (int w = 2; w <= N; w += 2) {
        FOR(l, 1, N+1 - (w - 1)) {
            int r = l + (w - 1);
            int n_A = A[r] - A[l-1];
            int n_T = T[r] - T[l-1];
            int n_C = C[r] - C[l-1];
            int n_G = G[r] - G[l-1];
            if (n_A == n_T && n_C == n_G) ans++;
        }
    }
    cout << ans << endl;

    return 0;
}
