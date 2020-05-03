import sys
from itertools import combinations_with_replacement

input = sys.stdin.readline
sys.setrecursionlimit(10 ** 7)


def main():
    N, M, Q = map(int, input().split())
    abcd = [None] * Q
    for i in range(Q):
        abcd[i] = tuple(map(int, input().split()))

    ans = 0
    for A in combinations_with_replacement(range(1, M+1), N):
        score = 0
        for q in abcd:
            a, b, c, d = q
            if A[b-1] - A[a-1] == c:
                score += d
        if score > ans:
            ans = score

    print(ans)


if __name__ == "__main__":
    main()
