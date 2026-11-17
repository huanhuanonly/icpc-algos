# 2026年码蹄杯 职业院校赛道 & 青少年挑战赛道入门组国赛
#
# => MC0544 燕王喜弃子求和 ( @c 钻石 )
#
# -> https://www.matiji.net/exam/brushquestion/44/4777/C98C14523F069FECB0DEED64F00CEAB0
#
# Submissions ~> https://www.matiji.net/exam/oj/submit-detail/20553072/44/4777/C98C14523F069FECB0DEED64F00CEAB0 By huanhuanonly
#
# @b Combinatorics
#
# ----August 27, 2026 [02h:31m:28s]----

n, m = map(int, input().split())
mod = 10 ** 9 + 7
print((m * (m - 1) * pow(m, n - 2, mod) * (n - 1) + pow(m, n, mod)) % mod)