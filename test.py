import sys
from collections import Counter

import numba as nb

input = sys.stdin.readline


@nb.njit("i8(UniTuple(i8),UniTuple(i8))")
def solve(keys, values):
    MAX_A = 10 ** 6
    divisible = [False] * (MAX_A + 1)
    ans = 0
    for k, v in zip(keys, values):
        if v == 1 and not divisible[k]:
            ans += 1
        for i in range(k, MAX_A + 1, k):
            divisible[i] = True
    return ans


def main():
    N = int(input())
    A = list(map(int, input().split()))

    A.sort()
    c = Counter(A)
    keys = tuple(c.keys())
    values = tuple(c.values())

    ans = solve(keys, values)
    print(ans)


if __name__ == "__main__":
    main()
