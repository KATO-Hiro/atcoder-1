想定解
-----

整数 $z$ の約数の個数を $D[z]$ とおきます．一つずつ約数列挙すると $O(N\sqrt{N})$ で間に合いません．ここで，ある整数 $d$ を用いてエラトステネスの篩の要領で $D[d], D[2d], D[3d], \cdots$ と $d$ の倍数に訪問する度にインクリメントすることで約数の個数を効率的に数え上げることができます．実際に篩はしないことに注意すると，調和級数の計算量解析により $O(N \mathrm{log}N)$ で解けます．

参考
-----

- [ABC170-D Not Divisible](https://atcoder.jp/contests/abc170/tasks/abc170_d)
- [ABC172-D Sum of Divisors](https://atcoder.jp/contests/abc172/tasks/abc172_d) (maspy さんのユーザ解説が参考になります)
