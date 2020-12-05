#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define SORT(c) sort(ALL(c))
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


VI compress_interval(VI& X1, VI& X2, int min_x, int max_x) {
    VI X;
    int N = SZ(X1);

    REP(i,N) {
        for (int d : {-1, 0, 1}) {
            int tx1 = X1[i] + d;
            int tx2 = X2[i] + d;
            if (min_x <= tx1 && tx1 <= max_x) X.push_back(tx1);
            if (min_x <= tx2 && tx2 <= max_x) X.push_back(tx2);
        }
    }

    SORT(X);
    X.erase(unique(ALL(X)), X.end());

    REP(i,N) {
        X1[i] = lower_bound(ALL(X), X1[i]) - X.begin();
        X2[i] = lower_bound(ALL(X), X2[i]) - X.begin();
    }

    return X;
}


// TODO: Verify

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);


    return 0;
}
