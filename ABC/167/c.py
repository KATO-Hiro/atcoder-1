import sys
from itertools import combinations

import numpy as np

input = sys.stdin.readline


def main():
    N, M, X = map(int, input().split())
    C = [0] * N
    A = np.zeros(shape=(N, M), dtype=int)
    for i in range(N):
        CA = list(map(int, input().split()))
        C[i], A[i] = CA[0], CA[1:]

    ans = float("inf")
    for i in range(1, 13):
        for comb in combinations(range(N), i):
            total = 0
            B = np.zeros(shape=M, dtype=int)
            for j in comb:
                total += C[j]
                B += A[j]
            if all(b >= X for b in B):
                if total < ans:
                    ans = total

    if ans == float("inf"):
        ans = -1

    print(ans)


if __name__ == "__main__":
    main()
