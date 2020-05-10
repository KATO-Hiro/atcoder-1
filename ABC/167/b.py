import sys

input = sys.stdin.readline


def main():
    A, B, C, K = map(int, input().split())

    if K <= A:
        ans = K
    elif K <= A + B:
        ans = A
    else:
        ans = A - (K - (A + B))

    print(ans)


if __name__ == "__main__":
    main()
