import sys
from math import sin, cos, radians, sqrt

input = sys.stdin.readline


def main():
    A, B, H, M = map(int, input().split())

    theta_A = radians(30 * (H + M / 60))
    x_A = A * cos(theta_A)
    y_A = A * sin(theta_A)

    theta_B = radians(6 * M)
    x_B = B * cos(theta_B)
    y_B = B * sin(theta_B)

    ans = sqrt((x_A - x_B)**2 + (y_A - y_B)**2)
    print(ans)


if __name__ == "__main__":
    main()
