from collections import Counter


def calc_prime_factors(n, count=False):
    """Trial division"""
    factors = []
    # factor: 2
    while n % 2 == 0:
        factors.append(2)
        n //= 2
    # factor: 3, 5, 7, 11, ...
    f = 3
    root_n = int(n ** 0.5) + 1
    while f <= root_n:
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


if __name__ == "__main__":
    print("calc_prime_factors:")
    N = int(input())
    factors = calc_prime_factors(N, count=True)
    print("factors = {}".format(factors))
    for factor in factors:
        print("(key, value) = {}".format(factor))
