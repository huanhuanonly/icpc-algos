/**
 * 牛客小白月赛128
 * 
 * => F-徽章计数 ( @c 1700 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/127265/F
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=81850024 By huanhuanonly
 * 
 * @b Combinatorics
 * 
 * ----January 30, 2026 [23h:11m:47s]----
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

template<typename _Tp>
[[nodiscard]] constexpr _Tp binary_exponentiation(_Tp __fv, _Tp __sv, _Tp __mod)
{
    auto res = static_cast<_Tp>(1);

    for (__fv %= __mod; __sv; __fv = (__fv * __fv) % __mod, __sv >>= 1)
    {
        if (__sv & 1)
        {
            res = (res * __fv) % __mod;
        }
    }

    return res;
}

inline namespace huanhuanonly {
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
}}

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
        int n, m;
        std::cin >> n >> m;

        std::vector<uint64> cnt(n + 1);

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;
            ++cnt[v];
        }

        constexpr uint64 mod = 1e9 + 7;

        uint64 ans = 1;

        for (int i = 1; i <= n; ++i)
        {
            if (cnt[i] == 0)
            {
                continue;
            }
            else if (cnt[i] % i or m == 0)
            {
                ans = 0;
                break;
            }
            
            for (; cnt[i]; cnt[i] -= i)
            {
                (ans *= C<mod>(cnt[i] - 1, i - 1)) %= mod;

                if (m == 0)
                {
                    ans = 0;
                    break;
                }

                (ans *= m--) %= mod;
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}