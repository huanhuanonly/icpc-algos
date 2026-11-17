# 牛客周赛 Round 150
#
# => E-小红的异或和 ( @c 1200 )
#
# -> https://ac.nowcoder.com/acm/contest/137073/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83991451 By huanhuanonly
#
# @b Bitwise-XOR
#
# ----July 11, 2026 [00h:30m:58s]----

def calc(n: int) -> int:
    if n % 4 == 0:
        return n
    elif n % 4 == 1:
        return 1
    elif n % 4 == 2:
        return n | 1
    else:
        return 0

l, r, x = map(int, input().split())
l = (l + x - 1) // x
r = r // x

if l <= r:
    print((calc(r) ^ calc(l - 1)) * x)
else:
    print('0')