/**
 * 牛客周赛 Round 150
 *
 * => F-小红的最长子序列 ( @c 1900 )
 *
 * -> https://ac.nowcoder.com/acm/contest/137073/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84011959 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----July 13, 2026 [18h:22m:19s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

inline namespace huanhuanonly {
    inline namespace math
{
template<
    typename _Tp, std::unsigned_integral _Up, typename _Mp,
    typename _MulOp = std::multiplies<_Tp>, typename _ModOp = std::modulus<void>>
requires
    requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; } and
    requires(_ModOp __op, _Tp __lhs, _Mp __rhs) { { __op(__lhs, __rhs) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _Mp __mod, _MulOp __mul_op = {}, _ModOp __mod_op = {})
{
    auto result = static_cast<_Tp>(1);

    for (__lhs = __mod_op(__lhs, __mod); __rhs; __lhs = __mod_op(__mul_op(__lhs, __lhs), __mod), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mod_op(__mul_op(result, __lhs), __mod);
        }
    }

    return result;
}

template<typename _Tp, std::unsigned_integral _Up, typename _MulOp = std::multiplies<_Tp>>
requires requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _MulOp __mul_op = {})
{
    auto result = static_cast<_Tp>(1);

    for (; __rhs; __lhs = __mul_op(__lhs, __lhs), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mul_op(result, __lhs);
        }
    }

    return result;
}
}} // namespace huanhuanonly::math

uint64 digit_count(uint64 n)
{
    if (n)
    {
        return static_cast<uint64>(log10(n)) + 1;
    }
    else
    {
        return 1;
    }
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::vector<uint64> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    std::vector dp(n + 1, std::vector(m, std::vector(m, std::pair(-200, 0))));
    dp[0][0][0].first = 0;

    std::vector last(n + 1, std::vector(m, std::vector(m, std::pair(0, 0))));

    for (int i = 1; i <= n; ++i)
    {
        dp[i] = dp[i - 1];

        const uint64 pow = binary_exponentiation(10ULL, digit_count(v[i]), m);

        for (uint64 sa = 0; sa < m; ++sa)
        {
            for (uint64 sb = 0; sb < m; ++sb)
            {
                const uint64 nsa = (sa + v[i]) % m;
                const uint64 nsb = (sb * pow + v[i]) % m;

                if (dp[i - 1][sa][sb].first + 1 > dp[i][nsa][nsb].first)
                {
                    dp[i][nsa][nsb] = {dp[i - 1][sa][sb].first + 1, i};
                    last[i][nsa][nsb] = {sa, sb};
                }
            }
        }
    }

    std::tuple mx{0, 0, 0};

    for (int i = 0; i < m; ++i)
    {
        mx = std::max(mx, std::tuple(dp.back()[i][i].first, dp.back()[i][i].second, i));
    }

    std::cout << std::get<0>(mx) << '\n';

    int pos = std::get<1>(mx);
    int sa = std::get<2>(mx), sb = sa;

    std::vector<int> ans;
    ans.reserve(std::get<0>(mx));

    while (pos)
    {
        ans.push_back(v[pos]);
        std::tie(sa, sb) = last[pos][sa][sb];
        pos = dp[pos - 1][sa][sb].second;
    }

    for (const int i : ans | std::views::reverse)
    {
        std::cout << i << ' ';
    }

    return 0;
}