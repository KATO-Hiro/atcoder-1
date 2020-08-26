import sys

input = sys.stdin.readline


def main():
    H1, M1, H2, M2, K = map(int, input().split())

    if H1 == H2:
        time = M2 - M1
    else:
        time = (60 - M1) + (H2 - H1 - 1) * 60 + M2

    ans = time - K
    print(ans)


if __name__ == "__main__":
    main()
