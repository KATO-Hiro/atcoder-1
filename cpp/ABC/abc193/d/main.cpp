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
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) (((b)>>(i)) & 1)
#define PCNT(b) __builtin_popcountll(b)
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << "l." << __LINE__ << " : " << #x << " = " << (x) << '\n'
ll llceil(ll a, ll b) { return (a + b - 1) / b; }
string toupper(const string& S) { string T(S); REP(i,SZ(T)) T[i] = toupper(T[i]); return T; }
string tolower(const string& S) { string T(S); REP(i,SZ(T)) T[i] = tolower(T[i]); return T; }
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VVS = vector<VS>;
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
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll K; cin >> K;
    string S; cin >> S;
    string T; cin >> T;

    unordered_map<ll,ll> cnt1,cnt2;
    REP(i,4) cnt1[(S[i] - '0')]++;
    REP(i,4) cnt2[(T[i] - '0')]++;

    VLL rem(10,K);
    for (auto& [a, n] : cnt1) rem[a] -= n;
    for (auto& [a, n] : cnt2) rem[a] -= n;
    ll total = 0; FOR(k,1,10) total += rem[k];
    FOR(k,1,10) debug(rem[k]);

    double ans = 0;
    FOR(i,1,10) FOR(j,1,10) {
        if (i == j) {
            if (rem[i] < 2) continue;
        } else {
            if (rem[i] == 0 || rem[j] == 0) continue;
        }
        cnt1[i]++; cnt2[j]++;
        ll a = 0;
        FOR(k,1,10) {
            ll tmp = 1; REP(_,cnt1[k]) tmp *= 10;
            a += k * tmp;
        }
        ll b = 0;
        FOR(k,1,10) {
            ll tmp = 1; REP(_,cnt2[k]) tmp *= 10;
            b += k * tmp;
        }
        if (a > b) {
            if (i == j) {
                ans += rem[i] * (rem[i] - 1);
            } else {
                ans += rem[i] * rem[j];
            }
        }
        cnt1[i]--; cnt2[j]--;
    }
    ans /= total * (total - 1);
    COUT(ans);

    return 0;
}
