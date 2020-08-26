import sys

input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))

    ans = 0
    for i, a in enumerate(A, start=1):
        if i % 2 == 1 and a % 2 == 1:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
