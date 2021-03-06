#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
// --------------------------------------------------------


struct Mex {
    int n = 0;
    int mex = 0;
    vector<bool> used;
    vector<int> v;
    Mex() : used(1, false) {}

    void add(int x) {
        assert(x >= 0);
        int size = used.size();

        // 2^n のタイミングで領域拡張
        n++;
        if (n == size) {
            size *= 2;
            used.resize(size);
            // v < 2^{n+1} を満たす v を used に反映
            int i = 0;
            while (i < (int)v.size()) {
                if (v[i] < size) {
                    used[v[i]] = true;
                    swap(v[i], v.back());
                    v.pop_back();
                } else {
                    i++;
                }
            }
        }

        if (x < size) {
            used[x] = true;
        } else {
            v.push_back(x);
        }
    }

    int query() {
        while (used[mex]) { mex++; }
        return mex;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL W(N); REP(i,N) cin >> W[i];
    VLL B(N); REP(i,N) cin >> B[i];

    const ll WW = 50;
    const ll BB = 1325;  // (1+2+..+50) + 50

    // nimber (grundy number)
    // 今の状態から一手で行ける状態の nimber に含まれていない最小の非負整数
    VVLL nim(WW+1,VLL(BB+1,-1));
    nim[0][0] = nim[0][1] = 0;
    auto rec = [&](auto self, ll w, ll b) -> ll {
        if (nim[w][b] != -1) return nim[w][b];

        Mex mex;
        if (w >= 1) mex.add(self(self, w-1, b+w));
        FOR(k,1,b/2+1) mex.add(self(self, w, b-k));

        return nim[w][b] = mex.query();
    };

    ll nimber = 0;
    REP(i,N) nimber ^= rec(rec, W[i], B[i]);
    string ans = (nimber != 0 ? "First" : "Second");
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/typical90/tasks/typical90_ae
