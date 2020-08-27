#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;


bool is_prime_number(ll n) {
  if (n == 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  ll f = 3, root_n = (ll)(sqrt(n) + 0.5);
  while (f <= root_n) {
    if (n % f == 0) return false;
    f += 2;
  }
  return true;
}


vector<bool> is_prime_numbers(ll n) {
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;

  ll root_n = (ll)(sqrt(n) + 0.5);
  for (int i = 2; i <= root_n; i++) {
    for (int j = 2 * i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }
  return is_prime;
}


int main() {
  int n, a, ans = 0;
  cin >> n;
  rep(i, n) {
    cin >> a;
    if (is_prime_number(a)) ans++;
  }
  cout << ans << endl;
  return 0;
}

/*
int main() {
  // Sieve of Eratosthenes
  ll n, MAX_V = 1e+8;
  cin >> n;

  vector<bool> is_prime = is_prime_numbers(MAX_V);
 
  int a, ans = 0;
  rep(i, n) {
    cin >> a;
    if (is_prime[a]) ans++;
  }
  cout << ans << endl;
  return 0;
}
*/

/*
https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C

input 1
-------
6
2
3
4
5
6
7

output 1
--------
4
*/