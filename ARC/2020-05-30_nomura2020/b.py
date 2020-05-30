import sys

input = sys.stdin.readline


def main():
    T = input().rstrip()

    ans = T.replace("?", "D", len(T))

    print(ans)


if __name__ == "__main__":
    main()
