#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


vector<ll> enumerate_divisors(ll n) {
  vector<ll> div_1, div_2;
  ll e, root_n = (ll)(sqrt(n) + 0.5);
  for (int d = 1; d <= root_n; d++) {
    if (n % d == 0) {
      div_1.push_back(d);
      e = n / d;
      if (e != d) div_2.push_back(e);
    }
  }
  reverse(div_2.begin(), div_2.end());
  div_1.insert(div_1.end(), div_2.begin(), div_2.end());
  return div_1;
}


int main() {
  ll N;
  cin >> N;

  auto F = [](ll A, ll B) -> int {
    return max(to_string(A).size(), to_string(B).size());
  };

  vector<ll> divisors = enumerate_divisors(N);
  int ans = 1 << 30;
  for (ll d: divisors) {
    ans = min(ans, F(d, N / d));
  }
  cout << ans << endl;
  return 0;
}


/*
https://atcoder.jp/contests/abc057/tasks/abc057_c

input 3
-------
9876543210

output 3
--------
6
*/