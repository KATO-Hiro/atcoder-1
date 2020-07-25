import sys

input = sys.stdin.readline


def main():
    N, K = map(int, input().split())
    A = tuple(map(int, input().split()))

    ans = [0] * (N - K)
    for i in range(N - K):
        if A[i] < A[K + i]:
            ans[i] = "Yes"
        else:
            ans[i] = "No"

    print("\n".join(ans))


if __name__ == "__main__":
    main()
