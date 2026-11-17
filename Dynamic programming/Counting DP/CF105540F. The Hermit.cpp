/**
 * 2024 China Collegiate Programming Contest (CCPC) Jinan Site (The 3rd Universal Cup. Stage 17: Jinan)
 *
 * => F. The Hermit
 *
 * -> https://codeforces.com/gym/105540/problem/F
 *
 * Submissions ~> https://codeforces.com/gym/105540/submission/391157169 By huanhuanonly
 *
 * @b Counting-DP
 * @b Number-theory ( @a greatest-common-divisor )
 *
 * ----September 19, 2026 [00h:59m:57s]----
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

inline namespace huanhuanonly {
    inline namespace math {
        inline namespace combinatorics
{
using comb_value_type = uint64;

constexpr auto comb_nmod = static_cast<comb_value_type>(0);

constexpr auto factorial_max_length = static_cast<std::size_t>(2e5 + 1);

template<comb_value_type _Mod = comb_nmod>
constexpr auto factorial{ []() constexpr
{
    std::array<comb_value_type, factorial_max_length> a{1};

    for (std::size_t i = 1; i < a.size(); ++i)
    {
        if constexpr (_Mod != comb_nmod)
        {
            a[i] = a[i - 1] * i % _Mod;
        }
        else
        {
            a[i] = a[i - 1] * i;
        }
    }

    return a;
}() };

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type C(comb_value_type n, comb_value_type k)
{
    if (n < k)
    {
        return 0;
    }

    if constexpr (_Mod != comb_nmod)
    {
        return factorial<_Mod>[n] * binary_exponentiation(factorial<_Mod>[n - k] * factorial<_Mod>[k] % _Mod, _Mod - 2, _Mod) % _Mod;
    }
    else
    {
        return factorial<_Mod>[n] / (factorial<_Mod>[n - k] * factorial<_Mod>[k]);
    }
}

template<comb_value_type _Mod>
[[nodiscard]] constexpr comb_value_type lucas(comb_value_type n, comb_value_type k)
{
    static_assert(_Mod != comb_nmod and _Mod > 1, "_Mod is required and must be a prime number.");

    if (k == 0)
    {
        return 1;
    }
    else
    {
        return C<_Mod>(n % _Mod, k % _Mod) * lucas<_Mod>(n / _Mod, k / _Mod) % _Mod;
    }
}

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type P(comb_value_type n, comb_value_type k)
{
    if (n < k)
    {
        return 0;
    }

    if constexpr (_Mod != comb_nmod)
    {
        assert(n < factorial_max_length);
        return factorial<_Mod>[n] * binary_exponentiation(factorial<_Mod>[n - k], _Mod - 2, _Mod) % _Mod;
    }
    else
    {
        assert(n < factorial_max_length);
        return factorial<_Mod>[n] / factorial<_Mod>[n - k];
    }
}

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type P(comb_value_type n)
{ return P<_Mod>(n, n); }

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type A(comb_value_type n, comb_value_type k)
{ return P<_Mod>(n, k); }

template<comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr comb_value_type A(comb_value_type n)
{ return P<_Mod>(n, n); }

template<comb_value_type _MaxN, comb_value_type _MaxK, comb_value_type _Mod = comb_nmod>
[[nodiscard]] constexpr auto comb_table() noexcept
{
    using table_type = std::array<std::array<comb_value_type, _MaxK>, _MaxN>;

    constexpr table_type table{ []() constexpr
        {
            table_type a{};

            for (std::size_t i = 0; i < a.size(); ++i)
            {
                a[i][0] = a[i][i] = 1;

                for (std::size_t j = 1; j < i; ++j)
                {
                    if constexpr (_Mod != comb_nmod)
                    {
                        a[i][j] = (a[i - 1][j] + a[i - 1][j - 1]) % _Mod;
                    }
                    else
                    {
                        a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
                    }
                }
            }

            return a;
        }()
    };

    return [&table](comb_value_type n, comb_value_type k) constexpr -> comb_value_type { return table[n][k]; };
}
}}} // namespace huanhuanonly::math::combinatorics

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int m, n;
    std::cin >> m >> n;

    constexpr uint64 mod = 998244353;
    constexpr int max_step = 18;

    std::vector<std::array<uint64, max_step + 1>> dp(m + 1);
    dp[1][1] = 1;

    for (int i = 2; i <= m; ++i)
    {
        dp[i][1] = 1;

        for (int d = 1; d * d <= i; ++d)
        {
            if (i % d == 0)
            {
                for (int j = 2; j <= max_step; ++j)
                {
                    (dp[i][j] += dp[d][j - 1]) %= mod;

                    if (i / d != d and d != 1)
                    {
                        (dp[i][j] += dp[i / d][j - 1]) %= mod;
                    }
                }
            }
        }
    }

    uint64 sum = 0;

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= std::min(n, max_step); ++j)
        {
            (sum += dp[i][j] * C<mod>(m / i - 1, n - j) % mod) %= mod;
        }
    }

    std::cout << (C<mod>(m, n) * n % mod + mod - sum) % mod << '\n';

    return 0;
}