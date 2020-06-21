import sys

input = sys.stdin.readline


def main():
    a = input().rstrip()

    if a.isupper():
        ans = "A"
    else:
        ans = "a"

    print(ans)


if __name__ == "__main__":
    main()
