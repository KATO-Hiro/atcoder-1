import os
import sys
sys.path.append(os.getcwd())  # NOQA

from lib.data.union_find import UnionFind

input = sys.stdin.readline


def main():
    V, E = map(int, input().split())
    stw = [None] * E
    for i in range(E):
        stw[i] = tuple(map(int, input().split()))

    stw.sort(key=lambda x: x[2])
    uf = UnionFind(V)

    ans = 0
    for s, t, w in stw:
        s += 1  # For AOJ input type (0-based)
        t += 1  # For AOJ input type (0-based)
        if uf.same_set(s, t):
            continue
        uf.union(s, t)
        ans += w

    print(ans)


if __name__ == "__main__":
    main()

"""
<http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A>

Example:
<input>
6 9
0 1 1
0 2 3
1 2 1
1 3 7
2 4 1
1 4 3
3 4 1
3 5 1
4 5 6
<output>
5
"""
