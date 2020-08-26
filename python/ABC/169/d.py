import sys
from collections import Counter

input = sys.stdin.readline


def calc_prime_factors(n, count=False):
    """Trial division"""
    factors = []
    # factor: 2
    while n % 2 == 0:
        factors.append(2)
        n //= 2
    # factor: 3, 5, 7, 11, ...
    f = 3
    while f ** 2 <= n:
        if n % f == 0:
            factors.append(f)
            n //= f
        else:
            f += 2
    if n != 1:
        factors.append(n)
    if count:
        factors = Counter(factors).items()
    return factors


def main():
    N = int(input())

    factors = calc_prime_factors(N, count=True)
    ans = 0
    for _, count in factors:
        n = 1
        while True:
            if n * (n + 1) // 2 <= count:
                n += 1
            else:
                break
        ans += (n - 1)

    print(ans)


if __name__ == "__main__":
    main()
