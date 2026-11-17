# AtCoder Beginner Contest 466
#
# => C - Count Close Pairs ( @c 300 )
#
# -> https://atcoder.jp/contests/abc466/tasks/abc466_c
#
# Submissions ~> https://atcoder.jp/contests/abc466/submissions/77381647 By huanhuanonly
#
# @b Interactive and @b Two-pointers
#
# ----July 11, 2026 [21h:45m:57s]----

def query(i, j):
    print('?', i, j)
    return input() == 'Yes'

def answer(x):
    print('!', x)

n = int(input())

cnt = 0

j = 1
for i in range(1, n  + 1):
    if i == j:
        j += 1

    while j <= n and query(i, j):
        j += 1

    cnt += j - i - 1

answer(cnt)