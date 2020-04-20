import sys

input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))

    ans = [0] * N
    for i in range(N-1):
        ans[A[i]-1] += 1

    print(*ans, sep="\n")


if __name__ == "__main__":
    main()
