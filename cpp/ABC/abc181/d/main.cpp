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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    int N = SZ(S);

    map<char,int> cnt;
    REP(i,N) cnt[S[i]]++;

    VS hachi;
    int x = 8;
    while (x < 1000) {
        string T = to_string(x);
        if (S == T) {
            cout << "Yes" << endl;
            return 0;
        }
        x += 8;
        if (SZ(T) == 2) {
            if (SZ(S) == 2) {
                if (S[0] == T[1] && S[1] == T[0]) {
                    cout << "Yes" << endl;
                    return 0;
                }
            }
        } else if (SZ(T) >= 3) {
            if (T.find('0') != string::npos) continue;
            hachi.push_back(T);
        }
    }

    string ans = "No";
    for (string t : hachi) {
        map<char,int> m;
        REP(i,3) m[t[i]]++;
        bool is_ok = true;
        for (auto s : m) {
            if (cnt[s.first] < s.second) is_ok = false;
        }
        if (is_ok) ans = "Yes";
    }
    cout << ans << '\n';

    return 0;
}
