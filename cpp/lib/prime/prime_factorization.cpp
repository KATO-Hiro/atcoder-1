#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


vector<ll> prime_factorization(ll n) {
  vector<ll> factors;
  ll f = 3, root_n = sqrt(n) + 1;

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
  int n;
  cin >> n;

  auto factors = prime_factorization(n);
  cout << n << ":";
  rep(i, factors.size()) cout << " " << factors[i];
  cout << endl;

  return 0;
}

/*
https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_A

input 2
-------
126

output 2
--------
126: 2 3 3 7

*/