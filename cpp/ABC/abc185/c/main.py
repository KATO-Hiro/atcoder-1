import sys

input = sys.stdin.readline


def main():
    L = int(input())

    ans = 1
    for i in range(1, 11 + 1):
        ans *= (L - i)
        ans //= i
    print(ans)


if __name__ == "__main__":
    main()
