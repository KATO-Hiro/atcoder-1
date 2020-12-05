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

    int N; cin >> N;
    string T; cin >> T;

    ll M = 1e10;
    if (T == "0" || T == "11" || T == "10") {
        COUT(M);
        return 0;
    }
    if (T == "1") {
        COUT(2*M);
        return 0;
    }
    if (T == "01") {
        COUT(M-1);
        return 0;
    }

    vector<char> S = {'1', '1', '0'};

    auto is_ok = [&](int x) -> bool {
        REP(i,N) {
            if (T[i] != S[x%3]) {
                return false;
            }
            x++;
        }
        return true;
    };

    ll num = 0;
    if (T.substr(0,3) == "110") {
        if (!is_ok(0)) {
            COUT(0); return 0;
        }
        num = (N+3-1) / 3;
    } else if (T.substr(0,3) == "101") {
        if (!is_ok(1)) {
            COUT(0); return 0;
        }
        num = 1 + ((N-2)+3-1)/3;
    } else if (T.substr(0,3) == "011") {
        if (!is_ok(2)) {
            COUT(0); return 0;
        }
        num = 1 + ((N-1)+3-1)/3;
    } else {
        COUT(0);
        return 0;
    }

    ll ans = M - (num - 1);
    cout << ans << '\n';

    return 0;
}
