import sys
from collections import Counter

input = sys.stdin.readline


def main():
    N = int(input())
    S = [None] * N
    for i in range(N):
        S[i] = input().rstrip()

    c = Counter(S)
    ans = len(c.keys())
    print(ans)


if __name__ == "__main__":
    main()
