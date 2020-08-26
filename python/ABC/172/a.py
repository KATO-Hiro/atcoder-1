import sys

input = sys.stdin.readline


def main():
    a = int(input())

    ans = a + a ** 2 + a ** 3

    print(ans)


if __name__ == "__main__":
    main()
