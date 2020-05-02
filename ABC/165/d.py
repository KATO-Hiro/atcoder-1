import sys
input = sys.stdin.readline


def main():
    A, B, N = map(int, input().split())

    x = min(B-1, N)
    ans = int(A*x/B) - A*int(x/B)
    print(ans)


if __name__ == "__main__":
    main()
