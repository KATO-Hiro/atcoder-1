#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


class SegmentTree {
    public:
        /**
         * @brief Construct a new Segment Tree object.
         * 
         * @param N Number of node.
         * @param init_v Initial value that does not affect _func.
         *               For example, specify INF when _func = min.
         * @param X Vector for initialization.
         */
        SegmentTree(int N, ll init_v, vector<ll> X) {
            _N = N;
            _init_v = init_v;
            _build(X);
        }

        /**
         * @brief Update the i-th node value to x.
         * 
         * @param i Index (1-based index).
         * @param x Update value.
         */
        void update(int i, ll x) {
            i += _N - 1;
            _node[i] = x;
            while (i > 1) {
                i >>= 1;
                _node[i] = _func(_node[i << 1], _node[i << 1 | 1]);
            }
        }

        /**
         * @brief Query for right half-open interval [l, r).
         * 
         * @param l Index (1-based index).
         * @param r Index (1-based index).
         * @return Result of the query.
         */
        ll query(int l, int r) {
            ll dst_l = _init_v;
            ll dst_r = _init_v;
            l += _N - 1;
            r += _N - 1;
            while (l < r) {
                if (l & 1) {
                    dst_l = _func(dst_l, _node[l]);
                    l++;
                }
                if (r & 1) {
                    r--;
                    dst_r = _func(_node[r], dst_r);
                }
                l >>= 1;
                r >>= 1;
            }
            return _func(dst_l, dst_r);
        }

    private:
        int _N;
        ll _init_v;
        vector<ll> _node;

        ll _func(ll x, ll y) {
            return min(x, y);
        }

        void _build(vector<ll> X) {
            // Initialize all nodes
            _node = vector<ll>(2 * _N, _init_v);  // 1-based index

            // Elementary intervals are stored
            for (int i = 0; i < _N; i++) {
                _node[i + _N] = X[i];
            }

            // The internal nodes correspond to intervals that are the union of elementary intervals
            for (int i = _N - 1; 0 < i; i--) {
                _node[i] = _func(_node[i << 1], _node[i << 1 | 1]);
            }
        }
};


int main() {
    int n, q;
    cin >> n >> q;

    ll INF = ((ll)1 << 31) - 1;
    vector<ll> a = vector<ll>(n, INF);
    auto st = SegmentTree(n, INF, a);

    ll com, x, y;
    vector<int> ans;
    rep(_, q) {
        cin >> com >> x >> y;
        if (com == 0) {
            // update
            x++;  // For AOJ input type (0-based index)
            st.update(x, y);
        }
        else {
            // find
            x++;  // For AOJ input type (0-based index)
            y++;  // For AOJ input type (0-based index)
            ans.push_back(st.query(x, y + 1));
        }
    }
    for (auto _ans: ans) cout << _ans << endl;
    return 0;
}


/*
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A

input 1
-------
3 5
0 0 1
0 1 2
0 2 3
1 0 2
1 1 2

output 1
--------
1
2

*/