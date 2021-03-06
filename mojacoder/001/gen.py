import glob
import os
import random
import shutil
import sys
from math import gcd

input = sys.stdin.readline
random.seed(777)

testdir = "./gcd-and-lcm/testcases"


def lcm(a, b):
    return (a * b) // gcd(a, b)


def write_testcase(name, A, B, G, L):
    with open(f"{testdir}/in/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{A} {G} {L}\n")

    with open(f"{testdir}/out/{name}.txt", "w", encoding="utf-8") as f:
        f.write(f"{B}\n")

    print(f"[{name}] (A, B, G, L) = ({A}, {B}, {G}, {L})")


def main():
    N = 10000
    T = 10  # 作成ケース数
    while T > 0:
        A = random.randint(1, N)
        B = random.randint(1, N)
        G = gcd(A, B)
        L = lcm(A, B)
        if not (1 <= G <= N): continue
        if not (1 <= L <= N): continue

        write_testcase(f"random-{T}", A, B, G, L)
        T -= 1

    # handmade
    write_testcase(f"hand-1", 1, 1, 1, 1)
    write_testcase(f"hand-2", 1234, 1234, 1234, 1234)
    write_testcase(f"hand-3", 97, 101, 1, 9797)
    write_testcase(f"hand-4", 123, 234, 3, 9594)

    # sample
    write_testcase(f"sample-1", 6, 9, 3, 18)

    # oj 用にコピー
    os.makedirs("test")
    for io in ("in", "out"):
        for infile in glob.glob(f"{testdir}/{io}/*.txt"):
            filename = os.path.basename(infile)[:-3] + io
            shutil.copy(infile, f"test/{filename}")


if __name__ == "__main__":
    main()
