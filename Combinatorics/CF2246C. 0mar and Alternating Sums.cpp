/**
 * Codeforces Round 1108 (Div. 2)
 *
 * => C. 0mar and Alternating Sums ( @c 1400 )
 *
 * -> https://codeforces.com/contest/2246/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/2246/submission/382280615 By huanhuanonly
 *
 * @b Combinatorics
 *
 * ----July 12, 2026 [23h:54m:39s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::map<int, int> cnt;

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;
            ++cnt[v];
        }

        constexpr uint64 mod = 1e9 + 7;

        if (cnt.contains(-1))
        {
            uint64 c = 1;

            if (cnt.size() > 1)
            {
                for (auto fit = cnt.begin(), sit = std::next(fit); sit != cnt.end(); ++fit, ++sit)
                {
                    if (fit->first + 1 == sit->first)
                    {
                        ++c;
                    }
                }
            }

            std::cout << c * binary_exponentiation(2ULL, n - cnt.size(), mod) % mod << '\n';
        }
        else
        {
            std::cout << binary_exponentiation(2ULL, n - cnt.size(), mod) << '\n';
        }
    }

    return 0;
}