import sys

input = sys.stdin.readline


def main():
    K = int(input())

    num = 0
    for i in range(1, 10 ** 7 // 2):
        num = ((num * 10) + 7) % K
        if num == 0:
            ans = i
            break

    else:
        ans = -1

    print(ans)


if __name__ == "__main__":
    main()
