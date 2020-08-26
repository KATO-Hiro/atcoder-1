import sys

input = sys.stdin.readline


def main():
    N, Q = map(int, input().split())
    A = list(map(int, input().split()))
    X = list(map(int, input().split()))

    ans = [0] * Q
    for i, x in enumerate(X):
        count = 0
        total = 0
        r = 0
        for l in range(N):
            while r < N and total + A[r] <= x:
                total += A[r]
                r += 1

            count += (r - l)

            if l == r:
                r += 1
            else:
                total -= A[l]

        ans[i] = count

    print("\n".join(map(str, ans)))


if __name__ == "__main__":
    main()

"""
<http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_C>

Example:
<input>
6 5
1 2 3 4 5 6
6 9 12 21 15
<output>
9
12
15
21
18
"""
