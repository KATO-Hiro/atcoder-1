import sys

input = sys.stdin.readline


def main():
    N = int(input())
    A = [0] * N
    B = [0] * N
    for i in range(N):
        A[i], B[i] = map(int, input().split())

    A.sort()
    B.sort()
    
    if N % 2 == 0:
        a = A[N // 2 - 1] + A[N // 2]
        b = B[N // 2 - 1] + B[N // 2]
        ans = (b - a) + 1
    else:
        a = A[N // 2]
        b = B[N // 2]
        ans = b - a + 1

    print(ans)


if __name__ == "__main__":
    main()
