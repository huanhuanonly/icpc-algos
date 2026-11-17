# => P16820 [蓝桥杯 2026 国 Python B] 控制机器人 ( @c 普及+/提高 )
#
# -> https://www.luogu.com.cn/problem/P16820
#
# Submissions ~> https://www.luogu.com.cn/record/281246816 By huanhuanonly
#
# @b Combinatorics ( @a catalan-numbers )
#
# ----June 08, 2026 [21h:08m:26s]----

mod = 998244353
fact = [1] * (2 * 10 ** 6 + 10)

for i in range(2, len(fact)):
    fact[i] = fact[i - 1] * i % mod

def C(n, k):
    if k < 0:
        return 0
    else:
        return fact[n] * pow(fact[n - k] * fact[k] % mod, mod - 2, mod) % mod

x, y, k = map(int, input().split())

if x < k:
    print('0')
else:
    x -= k
    y += k

    print((C(y + k, k) - C(y + k, k - 1)) * C(y + k + x, y + k) % mod)