import glob
import os
import random
import shutil
import sys

input = sys.stdin.readline
random.seed(777)

testdir = "./number-of-divisors-1/testcases"


def write_testcase(name, N):
    ans, M = solve(N)

    with open(f"{testdir}/in/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{N}\n")

    with open(f"{testdir}/out/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{ans}\n")

    print(f"[{name}] (N, M, ans) = ({N}, {M}, {ans})")


def solve(N):
    M = 1
    while (M + 1)**2 <= N:
        M += 1
    ans = 0
    ans += N * (N - 1) // 2
    ans -= M * (M - 1) // 2
    return ans, M


def main():
    MAX_N = 1000000
    T = 10  # 作成ケース数
    while T > 0:
        N = random.randint(2, 1000)
        write_testcase(f"random-small-{T}", N)
        T -= 1
    T = 10  # 作成ケース数
    while T > 0:
        N = random.randint(1000, MAX_N)
        write_testcase(f"random-large-{T}", N)
        T -= 1

    # handmade
    write_testcase(f"hand-1", 2)
    write_testcase(f"hand-2", 1023)
    write_testcase(f"hand-3", 1024)
    write_testcase(f"hand-4", 15128)
    write_testcase(f"hand-5", 15129)
    write_testcase(f"hand-6", 999999)

    # sample
    write_testcase(f"sample-1", 3)
    write_testcase(f"sample-2", 6)
    write_testcase(f"sample-3", 1000000)

    # oj 用にコピー
    os.makedirs("test")
    for io in ("in", "out"):
        for infile in glob.glob(f"{testdir}/{io}/*.txt"):
            filename = os.path.basename(infile)[:-3] + io
            shutil.copy(infile, f"test/{filename}")


if __name__ == "__main__":
    main()
