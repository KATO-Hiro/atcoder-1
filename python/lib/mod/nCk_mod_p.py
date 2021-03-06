P = 10**9 + 7


class MODCombination:
    def __init__(self, n, p):
        self.n = n
        self.p = p  # MOD
        self.fac, self.ifac = self.make_fac_tables_mod_p(n, p)

    @staticmethod
    def make_fac_tables_mod_p(n, p):
        assert n >= 1
        fac = [0] * (n + 1)   # _______ factorial: n!
        ifac = [0] * (n + 1)  # inverse factorial: n!^{-1}
        inv = [0] * (n + 1)   # inverse element  : n ^{-1}
        fac[0] = fac[1] = 1
        ifac[0] = ifac[1] = 1
        inv[1] = 1
        for i in range(2, n + 1):
            fac[i] = fac[i - 1] * i % p
            inv[i] = p - inv[p % i] * (p // i) % p
            ifac[i] = ifac[i - 1] * inv[i] % p
        return fac, ifac

    def nCk(self, n, k):
        # nCk = n! * k!^{-1} * (n-k)!^{-1}
        return ((self.fac[n] * self.ifac[n - k]) % self.p) * self.ifac[k] % self.p


def main():
    print("n, k:")
    n, k = map(int, input().split())

    mod_comb = MODCombination(n, P)
    ans = mod_comb.nCk(n, k)
    print(ans)


if __name__ == "__main__":
    main()
