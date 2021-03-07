import glob
import os
import random
import shutil
import subprocess
import sys
from collections import defaultdict

input = sys.stdin.readline
random.seed(777)

testdir = "./ax-by-zc/testcases"


def cleen():
    subprocess.run(f"rm {testdir}/*/*.txt", shell=True, cwd=os.curdir)
    subprocess.run(f"rm -r test/", shell=True, cwd=os.curdir)


def write_testcase(name, A, B, C, expected=None):
    ans = solve(A, B, C)
    if expected is not None:
        assert(ans == expected), f"ans != expected: {ans} != {expected}"

    with open(f"{testdir}/in/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{A} {B} {C}\n")

    with open(f"{testdir}/out/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{ans}\n")

    print(f"[{name}] (A, B, C, ans) = ({A}, {B}, {C}, {ans})")


def prime_factorization(n):
    factors = defaultdict(int)

    while n % 2 == 0:
        factors[2] += 1
        n //= 2

    f = 3
    root = int(n ** 0.5) + 1
    while f <= root:
        while n % f == 0:
            factors[f] += 1
            n //= f
        f += 2
    if n != 1:
        factors[n] += 1

    return factors


def solve(A, B, C):
    factors = defaultdict(int)
    for Z in (A, B):
        for f, n in prime_factorization(Z).items():
            factors[f] = max(factors[f], n)

    MOD = 1000000007
    z = 1
    for f, n in factors.items():
        m = (n + C - 1) // C
        for _ in range(m):
            z *= f

    # check
    zC = pow(z, C)
    assert(zC % A == 0), f"(A,B,C,zC) = ({A},{B},{C},{zC})"
    assert(zC % B == 0), f"(A,B,C,zC) = ({A},{B},{C},{zC})"

    ans = z % MOD
    return ans


def main():
    MAX_N = 1000000000000
    T = 10  # 作成ケース数
    while T > 0:
        A = random.randint(1, 1000000)
        B = random.randint(1, 1000000)
        C = random.randint(1, 3)
        write_testcase(f"random-small-{T}", A, B, C)
        T -= 1
    T = 10  # 作成ケース数
    while T > 0:
        A = random.randint(1000000000, MAX_N)
        B = random.randint(1000000000, MAX_N)
        C = random.randint(1, 3)
        write_testcase(f"random-large-{T}", A, B, C)
        T -= 1

    # handmade
    write_testcase(f"min-1-1", 1, 1, 1)
    write_testcase(f"min-1-2", 1, 1, 2)
    write_testcase(f"min-1-3", 1, 1, 3)
    write_testcase(f"min-2-1", 2, 2, 1)
    write_testcase(f"min-2-2", 2, 2, 2)
    write_testcase(f"min-2-3", 2, 2, 3)

    write_testcase(f"mid-1-1", 1000000, 1000000, 1)
    write_testcase(f"mid-1-2", 1000000, 1000000, 2)
    write_testcase(f"mid-1-3", 1000000, 1000000, 3)
    write_testcase(f"mid-2-1", 1234567, 9876543, 1)
    write_testcase(f"mid-2-2", 1234567, 9876543, 2)
    write_testcase(f"mid-2-3", 1234567, 9876543, 3)

    write_testcase(f"max-1-1", 1000000000000, 1000000000000, 1)
    write_testcase(f"max-1-2", 1000000000000, 1000000000000, 2)
    write_testcase(f"max-1-3", 1000000000000, 1000000000000, 3)
    write_testcase(f"max-2-1", 999999999999, 999999999999, 1)
    write_testcase(f"max-2-2", 999999999999, 999999999999, 2)
    write_testcase(f"max-2-3", 999999999999, 999999999999, 3)
    write_testcase(f"max-3-1", 987654321234, 123456789876, 1)
    write_testcase(f"max-3-2", 987654321234, 123456789876, 2)
    write_testcase(f"max-3-3", 987654321234, 123456789876, 3)
    write_testcase(f"max-4-1", 857732792025, 792573348236, 1)
    write_testcase(f"max-4-2", 857732792025, 792573348236, 2)
    write_testcase(f"max-4-3", 857732792025, 792573348236, 3)
    write_testcase(f"max-5-1", 998877665544, 112233445566, 1)
    write_testcase(f"max-5-2", 998877665544, 112233445566, 2)
    write_testcase(f"max-5-3", 998877665544, 112233445566, 3)

    write_testcase(f"mod-1-1", 1000000007, 7777777777, 1, 0)
    write_testcase(f"mod-1-2", 1000000007, 7777777777, 2, 0)
    write_testcase(f"mod-1-3", 1000000007, 7777777777, 3, 0)
    write_testcase(f"mod-2-1", 7777777777, 1000000007, 1, 0)
    write_testcase(f"mod-2-2", 7777777777, 1000000007, 2, 0)
    write_testcase(f"mod-2-3", 7777777777, 1000000007, 3, 0)
    write_testcase(f"mod-3-1", 1000000007, 1000000007, 1, 0)
    write_testcase(f"mod-3-2", 1000000007, 1000000007, 2, 0)
    write_testcase(f"mod-3-3", 1000000007, 1000000007, 3, 0)

    # 1048576 = 2**20
    # 1594323 = 3**13
    # (C = 1) = 2**20 * 3**13 % MOD = 768822351
    # (C = 2) = 2**10 * 3**7  % MOD = 2239488
    # (C = 3) = 2**7  * 3**5  % MOD = 31104
    write_testcase(f"hand-1-1", 1048576, 1594323, 1, 768822351)
    write_testcase(f"hand-1-2", 1048576, 1594323, 2, 2239488)
    write_testcase(f"hand-1-3", 1048576, 1594323, 3, 31104)

    # 238239225000 = 2**3 * 3**4 * 5**5 * 7**6
    # 403409160000 = 2**6 * 3**5 * 5**4 * 7**3 * 11**2
    #      (C = 1) = 2**6 * 3**5 * 5**5 * 7**6 * 11**2 % MOD = 704557078
    #      (C = 2) = 2**3 * 3**3 * 5**3 * 7**3 * 11**1 % MOD = 101871000
    #      (C = 3) = 2**2 * 3**2 * 5**2 * 7**2 * 11**1 % MOD = 485100
    write_testcase(f"hand-2-1", 238239225000, 403409160000, 1, 704557078)
    write_testcase(f"hand-2-2", 238239225000, 403409160000, 2, 101871000)
    write_testcase(f"hand-2-3", 238239225000, 403409160000, 3, 485100)

    # 9643339904 = 2**7 * 11**3 * 23**2 * 107
    # 1146273172 = 2**2 * 11**4 * 23**2 * 37
    #    (C = 1) = 2**7 * 11**4 * 23**2 * 37 * 107 % MOD = 839313460
    #    (C = 2) = 2**4 * 11**2 * 23**1 * 37 * 107 % MOD = 176286352
    #    (C = 3) = 2**3 * 11**2 * 23**1 * 37 * 107 % MOD = 88143176
    write_testcase(f"hand-3-1", 9643339904, 1146273172, 1, 839313460)
    write_testcase(f"hand-3-2", 9643339904, 1146273172, 2, 176286352)
    write_testcase(f"hand-3-3", 9643339904, 1146273172, 3, 88143176)

    # 27646512781 =         61**3 * 349**2
    # 25592071811 = 59**3 *                  353**2
    #     (C = 1) = 59**3 * 61**3 * 349**2 * 353**2 % MOD = 360568157
    #     (C = 2) = 59**2 * 61**2 * 349**1 * 353**1 % MOD = 746213632
    #     (C = 3) = 59**1 * 61**1 * 349**1 * 353**1 % MOD = 443386003
    write_testcase(f"hand-4-1", 27646512781, 25592071811, 1, 360568157)
    write_testcase(f"hand-4-2", 27646512781, 25592071811, 2, 746213632)
    write_testcase(f"hand-4-3", 27646512781, 25592071811, 3, 443386003)

    # sample
    write_testcase(f"sample-1", 90, 24, 2, 60)
    write_testcase(f"sample-2", 90, 24, 3, 30)
    write_testcase(f"sample-3", 72, 96, 3, 12)
    write_testcase(f"sample-4", 2147483647, 1000000009, 1, 294967266)

    # oj 用にコピー
    os.makedirs("test")
    for io in ("in", "out"):
        for infile in glob.glob(f"{testdir}/{io}/*.txt"):
            filename = os.path.basename(infile)[:-3] + io
            shutil.copy(infile, f"test/{filename}")


if __name__ == "__main__":
    cleen()
    main()
