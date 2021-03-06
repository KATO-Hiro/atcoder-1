import glob
import os
import random
import shutil
import subprocess
import sys

input = sys.stdin.readline
random.seed(777)

testdir = "./inverse-of-divisor/testcases"


def cleen():
    subprocess.run(f"rm {testdir}/*/*.txt", shell=True, cwd=os.curdir)
    subprocess.run(f"rm -r test/", shell=True, cwd=os.curdir)


def write_testcase(name, N):
    ans = solve(N)

    with open(f"{testdir}/in/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{N}\n")

    with open(f"{testdir}/out/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{ans}\n")

    print(f"[{name}] (N, ans) = ({N}, {ans})")


def solve(N):
    sum_divisors = 0
    for d in range(1, int(N**0.5) + 1):
        if N % d == 0:
            sum_divisors += d
            if N // d != d:
                sum_divisors += N // d
    ans = "Yes" if (sum_divisors % N == 0) else "No"
    return ans


def main():
    MAX_N = 1000000000000
    T = 10  # 作成ケース数
    while T > 0:
        N = random.randint(2, 1000000)
        write_testcase(f"random-small-{T}", N)
        T -= 1
    T = 10  # 作成ケース数
    while T > 0:
        N = random.randint(1000000, MAX_N)
        write_testcase(f"random-large-{T}", N)
        T -= 1

    # handmade
    write_testcase(f"hand-1", 2)
    write_testcase(f"hand-2", 28)
    write_testcase(f"hand-3", 100)
    write_testcase(f"hand-4", 120)
    write_testcase(f"hand-5", 123)
    write_testcase(f"hand-6", 672)
    write_testcase(f"hand-7", 12345)
    write_testcase(f"hand-8", 30240)
    write_testcase(f"hand-9", 123456)
    write_testcase(f"hand-10", 523776)
    write_testcase(f"hand-11", 1000000)
    write_testcase(f"hand-12", 2178540)
    write_testcase(f"hand-13", 23569920)
    write_testcase(f"hand-14", 1000000000)
    write_testcase(f"hand-15", 1000000007)
    write_testcase(f"hand-16", 14182439040)
    write_testcase(f"hand-17", 549755813888)
    write_testcase(f"hand-18", 999999999999)
    write_testcase(f"hand-19", 1000000000000)

    # sample
    write_testcase(f"sample-1", 6)
    write_testcase(f"sample-2", 5)

    # oj 用にコピー
    os.makedirs("test")
    for io in ("in", "out"):
        for infile in glob.glob(f"{testdir}/{io}/*.txt"):
            filename = os.path.basename(infile)[:-3] + io
            shutil.copy(infile, f"test/{filename}")


if __name__ == "__main__":
    cleen()
    main()
