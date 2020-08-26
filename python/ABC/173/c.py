import sys
from itertools import product

import numpy as np

input = sys.stdin.readline


def main():
    H, W, K = map(int, input().split())
    c = [None] * H
    for i in range(H):
        S = input().rstrip()
        c[i] = [1 if s == "#" else 0 for s in S]

    ans = 0
    for h_comb in product((True, False), repeat=H):
        for w_comb in product((True, False), repeat=W):
            grid = np.array(c, dtype=np.int64)
            for i, paint in enumerate(h_comb):
                if paint:
                    grid[i, :] = 0
            for i, paint in enumerate(w_comb):
                if paint:
                    grid[:, i] = 0
            if np.sum(grid) == K:
                ans += 1

    print(ans)


if __name__ == "__main__":
    main()
