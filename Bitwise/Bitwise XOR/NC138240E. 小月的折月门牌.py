# 牛客周赛 Round 155
#
# => E-小月的折月门牌 ( @c 1800 )
#
# -> https://ac.nowcoder.com/acm/contest/138240/E
#
# Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84335760 By huanhuanonly
#
# @b Bitwise-XOR
#
# ----August 02, 2026 [20h:21m:02s]----

k, q = map(int, input().split())

for _ in range(q):
    l, r, h, z = map(int, input().split())
    l, r = l - 1, r - 1

    z = ''.join(reversed(bin(z)[2:].rjust(h, '0'))).ljust(k, '0')

    s = ''
    f = False

    for i in range(h):
        if z[i] == '1':
            s += '0' if f else '1'
            f = not f
        else:
            s += '1' if f else '0'

    t = s + '1' * (k - h)
    s += '0' * (k - h)

    s, t = int(s, 2), int(t, 2)

    print(max(0, min(t, r) - max(s, l) + 1))