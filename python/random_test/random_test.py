import random
import subprocess

TESTCASE_FILE = "random.in"
MAIN_PROC = "main.py"
GREEDY_PROC = "greedy.py"


def read_random_case():
    with open(TESTCASE_FILE, "r", encoding="utf-8") as f:
        return " ".join(map(str, f.readlines()))


def write_random_case():
    with open(TESTCASE_FILE, "w", encoding="utf-8") as f:
        # 1 <= N, K <= 10
        N = random.randint(1, 10)
        K = random.randint(1, 10)
        f.write(f"{N} {K}")


def solve(proc_name):
    with open(TESTCASE_FILE, "r", encoding="utf-8") as f:
        res = subprocess.run(
            ["python3", proc_name], stdin=f, stdout=subprocess.PIPE, encoding="utf-8")
        return res.stdout


def main():
    while True:
        write_random_case()
        A = solve(MAIN_PROC)
        B = solve(GREEDY_PROC)
        if A != B:
            print("----------------------------------------")
            print("Wrong Answer")
            print("[test case] ")
            print(read_random_case())
            print(MAIN_PROC)
            print(A)
            print(GREEDY_PROC)
            print(B)
            print("----------------------------------------")


if __name__ == "__main__":
    main()
