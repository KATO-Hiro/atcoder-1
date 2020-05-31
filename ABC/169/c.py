import sys
from decimal import Decimal

input = sys.stdin.readline


def main():
    A, B = input().split()

    a = Decimal(A)
    b = Decimal(B)
    ans = a * b
    ans = int(ans)
    print(ans)


if __name__ == "__main__":
    main()
