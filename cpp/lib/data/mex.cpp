#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
// --------------------------------------------------------


// References:
//   <https://twitter.com/noshi91/status/1283759174791372809>

/**
 * @brief Mex : amortized O(1)
 * 
 */
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


// TODO: verify
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    Mex mex;
    cout << "mex = " << mex.query() << endl;
    mex.add(0);
    cout << "add 0" << endl;
    cout << "mex = " << mex.query() << endl;
    mex.add(2);
    cout << "add 2" << endl;
    cout << "mex = " << mex.query() << endl;
    mex.add(1);
    cout << "add 1" << endl;
    cout << "mex = " << mex.query() << endl;
    mex.add(4);
    cout << "add 4" << endl;
    cout << "mex = " << mex.query() << endl;
    mex.add(5);
    cout << "add 5" << endl;
    cout << "mex = " << mex.query() << endl;
    mex.add(3);
    cout << "add 3" << endl;
    cout << "mex = " << mex.query() << endl;

    return 0;
}
