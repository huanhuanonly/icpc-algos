/**
 * 2025 ICPC Wuhan Invitational Contest (The 3rd Universal Cup. Stage 37: Wuhan)
 *
 * => G. Path Summing Problem
 *
 * -> https://codeforces.com/gym/105901/problem/G
 *
 * Submissions ~> https://codeforces.com/gym/105901/submission/370015150 By huanhuanonly
 *
 * @b Sqrt-decomposition ( @a by-parameter )
 * @b Counting-DP
 * @b Combinatorics
 *
 * ----April 07, 2026 [01h:20m:15s]----
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
template<typename _Tp>
[[nodiscard]] constexpr _Tp binary_exponentiation(_Tp __lhs, _Tp __rhs, _Tp __mod)
{
    auto res = static_cast<_Tp>(1);

    for (__lhs %= __mod; __rhs; __lhs = (__lhs * __lhs) % __mod, __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            res = (res * __lhs) % __mod;
        }
    }

    return res;
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

    constexpr uint64 mod = 998244353;

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector v(n, std::vector(m, 0));

        std::vector<std::vector<std::pair<int, int>>> sets(n * m);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                std::cin >> v[i][j];
                --v[i][j];

                sets[v[i][j]].emplace_back(i, j);
            }
        }

        static auto calc = [](int h, int w) -> uint64
        {
            if (h <= 0 or w <= 0)
            {
                return 0;
            }
            else
            {
                return C<mod>(h + w - 2, h - 1);
            }
        };

        const int sq = static_cast<int>(std::sqrt(n * m));

        uint64 ans = 0;

        for (auto& set : sets)
        {
            std::ranges::sort(set);

            if (set.empty())
            {
                continue;
            }
            else if (set.size() <= sq)
            {
                std::vector<uint64> dp(set.size());

                for (int i = 0; i < int(dp.size()); ++i)
                {
                    dp[i] = calc(set[i].first + 1, set[i].second + 1);

                    for (int j = 0; j < i; ++j)
                    {
                        dp[i] += mod - dp[j] * calc(set[i].first - set[j].first + 1, set[i].second - set[j].second + 1) % mod;
                        dp[i] %= mod;
                    }

                    ans += dp[i] * calc(n - set[i].first, m - set[i].second) % mod;
                    ans %= mod;
                }
            }
            else
            {
                if (std::ranges::binary_search(set, std::pair(0, 0)))
                {
                    ans += calc(n, m);
                    ans %= mod;
                    continue;
                }

                std::vector dp(n, std::vector(m, uint64{}));
                dp[0][0] = 1;

                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < m; ++j)
                    {
                        if (not std::ranges::binary_search(set, std::pair(i, j)))
                        {
                            if (i)
                            {
                                dp[i][j] = dp[i - 1][j];
                            }

                            if (j)
                            {
                                dp[i][j] += dp[i][j - 1];
                                dp[i][j] %= mod;
                            }
                        }
                    }
                }

                for (const auto& [x, y] : set)
                {
                    uint64 sum = 0;

                    if (x)
                    {
                        sum = dp[x - 1][y];
                    }

                    if (y)
                    {
                        sum += dp[x][y - 1];
                    }

                    ans += sum * calc(n - x, m - y) % mod;
                    ans %= mod;
                }
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}