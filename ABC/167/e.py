import sys

input = sys.stdin.readline

P = 998244353


def make_fac_tables_mod_p(n, p):
    fac = [0] * (n + 1)
    fac_inv = [0] * (n + 1)
    mod_inv = [0] * (n + 1)
    fac[0] = fac[1] = 1
    fac_inv[0] = fac_inv[1] = 1
    mod_inv[1] = 1
    for i in range(2, n + 1):
        fac[i] = (fac[i - 1] * i) % p
        mod_inv[i] = p - mod_inv[p % i] * (p // i) % p
        fac_inv[i] = fac_inv[i - 1] * mod_inv[i] % p
    return fac, fac_inv


def nCk_mod_p(fac, fac_inv, n, k, p):
    return ((fac[n] * fac_inv[n - k]) % p) * fac_inv[k] % p


def main():
    N, M, K = map(int, input().split())

    fac, fac_inv = make_fac_tables_mod_p(N, P)

    ans = M * pow(M - 1, N - 1, mod=P) % P  # k = 0
    for k in range(1, K + 1):
        num = M * pow(M - 1, N - 1 - k, mod=P) % P
        num = num * nCk_mod_p(fac, fac_inv, N - 1, k, P) % P
        ans = (ans + num) % P

    print(ans)


if __name__ == "__main__":
    main()
