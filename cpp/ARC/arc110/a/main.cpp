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


vector<ll> prime_factorization(ll n) {
    vector<ll> factors;
    ll f = 3, root_n = (ll)(sqrt(n) + 0.5);

    // factor: 2
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    // factor: 3, 5, 7, 11, ...
    while (f <= root_n) {
        if (n % f == 0) {
            factors.push_back(f);
            n /= f;
        }
        else {
            f += 2;
        }
    }

    if (n != 1) factors.push_back(n);
    return factors;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;

    map<ll,ll> mp;
    FOR(i,2,N+1) {
        auto fs = prime_factorization(i);
        map<ll,ll> mm;
        for (ll f : fs) {
            mm[f]++;
        }
        for (auto m : mm) {
            ll f = m.first;
            ll n = m.second;
            chmax(mp[f], n);
        }
    }

    ll ans = 1;
    for (auto m : mp) {
        REP(_,m.second) ans *= m.first;
    }
    ans++;
    cout << ans << '\n';

    return 0;
}
