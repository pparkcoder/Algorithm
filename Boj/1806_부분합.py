# https://www.acmicpc.net/problem/1806

import sys
input = sys.stdin.readline

N, M = map(int, input().split())
numbers = list(map(int, input().split()))
start = end = 0
sums = numbers[end]
min_length = 100000
while (start <= end):
    if (sums >= M):
        min_length = min(min_length, end - start + 1)
        sums -= numbers[start]
        start += 1
    else :
        end += 1
        if (end >= N) :
            break
        else :
            sums += numbers[end]
result = 0 if min_length == 100000 else min_length
print(result)
