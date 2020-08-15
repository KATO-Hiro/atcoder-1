import sys

input = sys.stdin.readline


def main():
    S = input().rstrip()

    if "RRR" in S:
        ans = 3
    elif "RR" in S:
        ans = 2
    elif "R" in S:
        ans = 1
    else:
        ans = 0

    print(ans)


if __name__ == "__main__":
    main()
