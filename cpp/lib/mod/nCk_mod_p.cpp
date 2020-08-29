#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


class MODCombination {
    public:
        MODCombination(int n, int p) {
            _n = n;
            _p = p;
            _make_fac_tables_mod_p();
        }

        ll nCk(int n, int k) { return ((_fac[n] * _ifac[n - k]) % _p) * _ifac[k] % _p; }

    private:
        int _n, _p;
        vector<ll> _fac, _ifac, _inv;
        void _make_fac_tables_mod_p() {
            if (_n < 1) throw "n must be more than 0.";
            _fac = vector<ll>(_n + 1, 0);
            _ifac = vector<ll>(_n + 1, 0);
            _inv = vector<ll>(_n + 1, 0);
            _fac[0] = 1; _fac[1] = 1;
            _ifac[0] = 1; _ifac[1] = 1;
            _inv[1] = 1;
            for (int i = 2; i <= _n; i++) {
                _fac[i] = _fac[i - 1] * i % _p;
                _inv[i] = _p - _inv[_p % i] * (_p / i) % _p;
                _ifac[i] = _ifac[i - 1] * _inv[i] % _p;
            }
        }
};


int main() {
    const int P = 1e+9 + 7;
    int H, W;
    cin >> H >> W;
    H--; W--;

    auto mod_comb = MODCombination(W + H, P);
    auto ans = mod_comb.nCk(W + H, H);
    cout << ans << endl;
    return 0;
}

/*
https://atcoder.jp/contests/abc034/tasks/abc034_c

Input 1
-------
123 456

Output 1
--------
210368064

*/