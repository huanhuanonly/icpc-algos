/**
 * AtCoder Beginner Contest 353
 *
 * => D - Another Sigma Problem ( @c 400 )
 *
 * -> https://atcoder.jp/contests/abc353/tasks/abc353_d
 *
 * Submissions ~> https://atcoder.jp/contests/abc353/submissions/78138720 By huanhuanonly
 *
 * @b Combinatorics
 *
 * ----August 05, 2026 [23h:43m:34s]----
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

int digit_count(uint64 n)
{
    if (n)
    {
        return std::floor(std::log10(n)) + 1;
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

    int n;
    std::cin >> n;

    std::vector<uint64> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    constexpr uint64 mod = 998244353;
    uint64 sum = 0;

    std::array<uint64, 11> cnt{};

    for (int i = 0; i < n; ++i)
    {
        ++cnt[digit_count(v[i])];
    }

    for (int i = 0; i < n; ++i)
    {
        --cnt[digit_count(v[i])];

        for (uint64 c = 1; c < cnt.size(); ++c)
        {
            sum += v[i] * binary_exponentiation(10ULL, c) % mod * cnt[c] % mod;
            sum %= mod;
        }

        sum += v[i] * i % mod;
        sum %= mod;
    }

    std::cout << sum << '\n';

    return 0;
}