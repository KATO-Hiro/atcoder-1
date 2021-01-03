#include <bits/stdc++.h>
using namespace std;
// --------------------------------------------------------

// reference: https://boostjp.github.io/tips/multiprec-int.html
#include <boost/multiprecision/cpp_int.hpp>
typedef boost::multiprecision::cpp_int bint;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    bint A; cin >> A;
    bint B; cin >> B;

    bint ans = A + B;
    cout << ans << '\n';

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_2_A&lang=ja
//     please use language: C++11 (not C++17)
