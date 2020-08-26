import sys

import numba as nb
import numpy as np

input = sys.stdin.readline

P = 10 ** 9 + 7


@nb.njit("i8(i8,i8[:],i8)", cache=True)
def solve(D, N, L):
    dp = np.zeros(shape=(L + 1, 2, D), dtype=np.int64)
    dp[0][0][0] = 1
    for i in range(L):
        n = N[i]
        for j in range(2):
            max_d = 9 if j == 1 else n
            for d in range(max_d + 1):
                next_j = int(j or d < n)
                for r in range(D):
                    next_r = (r + d) % D
                    dp[i + 1][next_j][next_r] += dp[i][j][r]

        for r in range(D):
            dp[i + 1][0][r] %= P
            dp[i + 1][1][r] %= P

    return (dp[L][0][0] + dp[L][1][0] - 1) % P


def main():
    D = int(input())
    N = np.array(list(map(int, input().rstrip())), dtype=np.int64)

    L = len(N)
    ans = solve(D, N, L)

    print(ans)


if __name__ == "__main__":
    main()


"""
<https://atcoder.jp/contests/tdpc/submissions/15890104>

Example:
<input>
7
123456789012345678901234567890
<output>
468357804
"""
