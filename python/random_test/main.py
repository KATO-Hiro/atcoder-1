import sys

input = sys.stdin.readline


def main():
    N, K = map(int, input().split())
    print(N * K)


if __name__ == "__main__":
    main()
