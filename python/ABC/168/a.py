import sys

input = sys.stdin.readline


def main():
    N = input().rstrip()

    d = N[-1]
    if d in ["2", "4", "5", "7", "9"]:
        ans = "hon"
    elif d in ["0", "1", "6", "8"]:
        ans = "pon"
    else:
        ans = "bon"

    print(ans)


if __name__ == "__main__":
    main()
