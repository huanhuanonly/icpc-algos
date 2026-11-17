/**
 * AtCoder Beginner Contest 468
 *
 * => E - Sum of Average ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc468/tasks/abc468_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc468/submissions/78495401 By huanhuanonly
 *
 * @b Number-theory ( @a modular-inverse )
 *
 * ----August 18, 2026 [00h:57m:02s]----
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    uint64 n;
    std::cin >> n;

    constexpr uint64 mod = 998244353;

    std::vector<uint64> v(n + 1);

    for (uint64 i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        (v[i] += v[i - 1]) %= mod;
    }

    std::vector<uint64> inv(n + 1);

    for (uint64 i = 1; i <= n; ++i)
    {
        inv[i] = (inv[i - 1] + binary_exponentiation(i, mod - 2, mod)) % mod;
    }

    uint64 sum = 0;

    for (uint64 i = 1; i <= n; ++i)
    {
        (sum += v[i] * inv[i] % mod + mod - v[i - 1] * inv[n - i + 1] % mod) %= mod;
    }

    std::cout << sum << '\n';

    return 0;
}