import sys
from string import ascii_lowercase as a2z

input = sys.stdin.readline


def main():
    N = int(input())

    i = 1
    min_v = 1
    max_v = 26
    while True:
        if N <= max_v:
            j = N - min_v
            ans = ""
            for _ in range(i):
                r = j % 26
                ans = "".join([a2z[r], ans])
                j = (j - r) // 26
            break
        min_v += 26 ** i
        i += 1
        max_v += 26 ** i

    print(ans)


if __name__ == "__main__":
    main()
