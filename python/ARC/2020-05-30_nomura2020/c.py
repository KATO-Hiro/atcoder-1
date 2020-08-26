import sys
from itertools import accumulate as accum

input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))

    B = list(accum((A[1:])[::-1]))[::-1]

    ans = 1
    v_count = 1
    for a, b in zip(A[:-1], B):
        if a > 0:
            if a > v_count:
                ans = -1
                break
            else:
                v_count -= a
        v_count = min(2 * v_count, b)
        ans += v_count

    if v_count != A[-1]:
        ans = -1

    print(ans)


if __name__ == "__main__":
    main()
