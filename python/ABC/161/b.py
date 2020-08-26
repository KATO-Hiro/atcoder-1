import sys

input = sys.stdin.readline


def main():
    N, M = map(int, input().split())
    A = list(map(int, input().split()))
    sum_A = sum(A)

    cnt = 0
    for i in range(N):
        if A[i] >= sum_A / (4 * M):
            cnt += 1

    if cnt >= M:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
