import sys
from bisect import bisect_left

input = sys.stdin.readline


def binary_search(L, a, high):
    ng = -1
    ok = high
    while ok - ng > 1:
        mid = (ok + ng) // 2
        if a <= L[mid]:
            ok = mid
        else:
            ng = mid
    return ok


def main():
    N = int(input())
    A = [0] * N
    for i in range(N):
        A[i] = int(input())

    L = [0] * N
    L[0] = A[0]
    length = 1
    for a in A[1:]:
        if L[length - 1] < a:
            L[length] = a
            length += 1
        else:
            j = bisect_left(L, a, hi=length)
            L[j] = a

    print(length)


if __name__ == "__main__":
    main()

"""
<http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D>

Example:
<input>
5
5
1
3
2
4
<output>
3
"""
