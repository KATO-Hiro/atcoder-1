import sys
from collections import Counter

input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))
    Q = int(input())
    BC = [None] * Q
    for i in range(Q):
        BC[i] = map(int, input().split())

    c = Counter(A)
    d = dict(c.items())
    S = sum(k * v for k, v in c.items())
    for B, C in BC:
        if B in d:
            v = d[B]
            if C in d:
                d[C] += v
            else:
                d[C] = v
            d[B] = 0
            S = S + (C - B) * v
        print(S)


if __name__ == "__main__":
    main()
