import glob
import os
import random
import shutil
import subprocess
import sys

input = sys.stdin.readline
random.seed(777)

testdir = "./number-of-divisors-2/testcases"


def cleen():
    subprocess.run(f"rm {testdir}/*/*.txt", shell=True, cwd=os.curdir)
    subprocess.run(f"rm -r test/", shell=True, cwd=os.curdir)


def write_testcase(name, N, K):
    ans = solve(N, K)

    with open(f"{testdir}/in/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{N} {K}\n")

    with open(f"{testdir}/out/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{ans}\n")

    print(f"[{name}] (N, K, ans) = ({N}, {K}, {ans})")


def solve(N, K):
    D = [0] * (N + 1)
    for i in range(1, N + 1):
        for j in range(i, N + 1, i):
            D[j] += 1
    ans = 0
    for i in range(1, N + 1):
        if D[i] == K:
            ans += 1
    return ans


def main():
    MAX_N = 1000000
    T = 10  # 作成ケース数
    while T > 0:
        N = random.randint(2, 1000)
        K = random.randint(2, 10)
        write_testcase(f"random-small-{T}", N, K)
        T -= 1
    T = 10  # 作成ケース数
    while T > 0:
        N = random.randint(1000, MAX_N)
        K = random.randint(2, 100)
        write_testcase(f"random-large-{T}", N, K)
        T -= 1

    # handmade
    write_testcase(f"hand-1", 1, 1)
    write_testcase(f"hand-2", 1, 1000)
    write_testcase(f"hand-3", 1, 1000000)
    write_testcase(f"hand-4", 1000, 1)
    write_testcase(f"hand-5", 1000000, 1)
    write_testcase(f"hand-6", 1000000, 1000000)
    write_testcase(f"hand-7", 12345, 12)
    write_testcase(f"hand-8", 111111, 77)
    write_testcase(f"hand-9", 2222, 4)
    write_testcase(f"hand-10", 77777, 7)
    write_testcase(f"hand-11", 1024, 10)
    write_testcase(f"hand-12", 999999, 123)
    write_testcase(f"hand-13", 999999, 999999)
    write_testcase(f"hand-14", 1000000, 1)
    write_testcase(f"hand-15", 1000000, 2)
    write_testcase(f"hand-16", 1000000, 3)
    write_testcase(f"hand-17", 1000000, 4)
    write_testcase(f"hand-18", 1000000, 5)
    write_testcase(f"hand-19", 1000000, 6)
    write_testcase(f"hand-20", 1000000, 7)

    # sample
    write_testcase(f"sample-1", 5, 2)
    write_testcase(f"sample-2", 120, 6)
    write_testcase(f"sample-3", 1000000, 10)

    # oj 用にコピー
    os.makedirs("test")
    for io in ("in", "out"):
        for infile in glob.glob(f"{testdir}/{io}/*.txt"):
            filename = os.path.basename(infile)[:-3] + io
            shutil.copy(infile, f"test/{filename}")


if __name__ == "__main__":
    cleen()
    main()
