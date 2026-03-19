/**
 * Educational Codeforces Round 186 (Rated for Div. 2)
 * 
 * => D. Christmas Tree Decoration ( @c 1600 )
 * 
 * -> https://codeforces.com/contest/2182/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/2182/submission/355792794 By huanhuanonly
 * 
 * @b Combinatorics
 * 
 * ----December 30, 2025 [01h:43m:41s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

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

constexpr auto factorial_max_length = static_cast<std::size_t>(1e2 + 1);

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
constexpr comb_value_type C(comb_value_type n, comb_value_type k)
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
constexpr comb_value_type lucas(comb_value_type n, comb_value_type k)
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
constexpr comb_value_type P(comb_value_type n, comb_value_type k)
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
constexpr comb_value_type P(comb_value_type n)
{ return P<_Mod>(n, n); }

template<comb_value_type _Mod = comb_nmod>
constexpr comb_value_type A(comb_value_type n, comb_value_type k)
{ return P<_Mod>(n, k); }

template<comb_value_type _Mod = comb_nmod>
constexpr comb_value_type A(comb_value_type n)
{ return P<_Mod>(n, n); }
}}


int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int64 n, s;
        std::cin >> n >> s;

        std::vector<int64> v(n);

        for (int64& i : v)
        {
            std::cin >> i;
        }

        std::ranges::sort(v, std::ranges::greater{});

        constexpr int64 mod = 998244353;

        int64 cnt = 0;

        for (int64 i = 0; i < n; ++i)
        {
            if (v[i] == v.front())
            {
                ++cnt;
            }
            else
            {
                s -= v.front() - 1 - v[i];
            }
        }

        if (s < 0)
        {
            std::cout << 0 << '\n';
        }
        else if (s >= n - cnt)
        {
            std::cout << P<mod>(n) << '\n';
        }
        else
        {
            std::cout << P<mod>(cnt) * P<mod>(n - cnt) % mod * C<mod>(cnt + s, cnt) % mod << '\n';
        }
    }

    return 0;
}