import math
import sys


input = sys.stdin.readline


def main():
    K = int(input())

    ans = 0
    for a in range(1, K + 1):
        for b in range(1, K + 1):
            ab = math.gcd(a, b)
            for c in range(1, K + 1):
                ans += math.gcd(ab, c)
    print(ans)


if __name__ == "__main__":
    main()
