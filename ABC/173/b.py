import sys

input = sys.stdin.readline


def main():
    N = int(input())

    count = {"AC": 0, "WA": 0, "TLE": 0, "RE": 0}
    for _ in range(N):
        S = input().rstrip()
        count[S] += 1

    print(f"AC x {count['AC']}")
    print(f"WA x {count['WA']}")
    print(f"TLE x {count['TLE']}")
    print(f"RE x {count['RE']}")


if __name__ == "__main__":
    main()
