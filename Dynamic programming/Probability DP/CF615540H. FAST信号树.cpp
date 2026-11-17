/**
 * 2025-2026 国际大学生程序设计竞赛贵州省赛
 *
 * => H. FAST信号树
 *
 * -> https://codeforces.com/gym/615540/problem/H
 *
 * Submissions ~> https://codeforces.com/gym/615540/submission/388592598 By huanhuanonly
 *
 * @b Expectation-DP and @b Tree-DP
 *
 * ----August 28, 2026 [00h:16m:33s]----
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

    int n;
    std::cin >> n;

    constexpr uint64 mod = 1e9 + 7;

    std::vector<uint64> p(n + 1);
    std::vector<std::vector<int>> e(n + 1);

    for (int i = 2; i <= n; ++i)
    {
        uint64 fa, x, y;
        std::cin >> fa >> x >> y;

        p[i] = (y + mod - x) * binary_exponentiation(y, mod - 2, mod) % mod;
        e[fa].push_back(i);
    }

    std::vector<uint64> size(n + 1);

    std::vector<uint64> dp(n + 1);
    std::vector<uint64> sum(n + 1);

    auto dfs = [&](const auto& self, int u) -> void
    {
        size[u] = 1;

        for (const auto& v : e[u])
        {
            self(self, v);

            size[u] += size[v];
            (sum[u] += sum[v]) %= mod;
        }

        const auto t = p[u] * binary_exponentiation(size[u], mod - 2, mod) % mod;
        dp[u] = (1 + t * sum[u]) % mod * binary_exponentiation(mod + mod + 1 - t - t * (size[u] - 1) % mod, mod - 2, mod) % mod;

        (sum[u] += dp[u] * size[u]) %= mod;
    };

    dfs(dfs, 1);

    auto calc = [&](const auto& self, int u, int fa) -> void
    {
        (dp[u] += dp[fa]) %= mod;

        for (const auto& v : e[u])
        {
            self(self, v, u);
        }
    };

    dp[1] = 0;
    calc(calc, 1, 0);

    for (int i = 2; i <= n; ++i)
    {
        std::cout << dp[i] << '\n';
    }

    return 0;
}