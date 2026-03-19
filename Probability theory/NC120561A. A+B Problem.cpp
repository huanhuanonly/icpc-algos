/**
 * 2026牛客寒假算法基础集训营1
 * 
 * => A-A+B Problem ( @c 1500 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120561/A
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=81937750 By huanhuanonly
 * 
 * @b Probability-theory
 * 
 * ----February 04, 2026 [17h:46m:33s]----
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

inline namespace huanhuanonly
{
template<typename _Tp, _Tp _Modulus>
class StaticModular
{
public:

    using value_type = _Tp;
    using reference = _Tp&;
    using const_reference = const _Tp&;

    constexpr StaticModular(value_type __value = {}) noexcept
        : _M_value(residue(__value))
    { }

    constexpr value_type value() const noexcept
    { return _M_value; }

    static constexpr value_type modulus() noexcept
    { return _Modulus; }

    template<typename _Ty>
    static constexpr _Ty residue(_Ty __x) noexcept
    {
        if constexpr (std::is_unsigned_v<_Ty>)
        {
            return __x % modulus();
        }
        else
        {
            return (__x % static_cast<_Ty>(modulus()) + static_cast<_Ty>(modulus())) % modulus();
        }
    }

    template<typename _Ty>
    constexpr StaticModular power(_Ty __x) const noexcept
    {
        StaticModular result(static_cast<value_type>(1));
        auto t = *this;

        for (; __x; t *= t, __x >>= 1)
        {
            (__x & 1) ? void(result *= t) : void();
        }

        return result;
    }

    constexpr StaticModular inverse() const noexcept
    {
        if constexpr (std::is_integral_v<value_type>)
        {
            assert(std::gcd(_M_value, modulus()) == 1);
        }

        auto extended_euclid = [&](const auto& self, auto a, decltype(a) b) -> std::array<decltype(a), 2>
        {
            if (b == 0)
            {
                return {1, 0};
            }

            auto [x, y] = self(self, b, a % b);
            return {{y, x - a / b * y}};
        };

        if constexpr (std::is_signed_v<value_type>)
        {
            return static_cast<value_type>(residue(extended_euclid(extended_euclid, _M_value, modulus())[0]));
        }
        else if constexpr (std::is_unsigned_v<value_type>)
        {
            return static_cast<value_type>(residue(extended_euclid(extended_euclid, std::make_signed_t<value_type>(_M_value), std::make_signed_t<value_type>(modulus()))[0]));
        }
        else
        {
            return static_cast<value_type>(residue(extended_euclid(extended_euclid, __int128_t(_M_value), __int128_t(modulus()))[0]));
        }
    }

    template<typename _Ty>
    constexpr _Ty cast() const noexcept
    { return static_cast<_Ty>(_M_value); }


    constexpr StaticModular& operator=(value_type __value) noexcept
    { _M_value = residue(__value); return *this; }

    constexpr operator value_type() const noexcept
    { return _M_value; }

    constexpr std::strong_ordering operator<=>(value_type __x) const noexcept
    { return _M_value <=> __x; }

    constexpr std::strong_ordering operator<=>(StaticModular __other) const noexcept
    { return _M_value <=> __other._M_value; }

    constexpr reference operator*() noexcept
    { return _M_value; }
    
    constexpr const_reference operator*() const noexcept
    { return _M_value; }

    constexpr bool operator!() const noexcept
    { return !_M_value; }

    constexpr StaticModular operator~() const noexcept
    { return ~_M_value; }

    constexpr StaticModular operator+() const noexcept
    { return +_M_value; }

    constexpr StaticModular operator-() const noexcept
    { return -_M_value; }

    constexpr StaticModular& operator++() noexcept
    { _M_value = residue(++_M_value); return *this; }

    constexpr StaticModular& operator--() noexcept
    { _M_value -= 1; return *this; }

    constexpr StaticModular operator++(int) noexcept
    { auto t = *this; ++*this; return t; }

    constexpr StaticModular operator--(int) noexcept
    { auto t = *this; --*this; return t; }

    constexpr StaticModular operator+(value_type __x) const noexcept
    { return _M_value + residue(__x); }

    constexpr StaticModular operator-(value_type __x) const noexcept
    { return _M_value + modulus() - residue(__x); }
    
    constexpr StaticModular operator*(value_type __x) const noexcept
    { auto t = *this; t *= __x; return t; }

    constexpr StaticModular operator/(value_type __x) const noexcept
    { return *this * StaticModular(__x).inverse(); }

    constexpr StaticModular operator%(value_type __x) const noexcept
    { return _M_value % __x; }

    constexpr StaticModular& operator+=(value_type __x) noexcept
    { return *this = *this + __x; }
    
    constexpr StaticModular& operator-=(value_type __x) noexcept
    { return *this = *this - __x; }

    constexpr StaticModular& operator*=(value_type __x) noexcept
    {
        if constexpr (std::numeric_limits<value_type>::max() / modulus() >= modulus())
        {
            _M_value = residue(_M_value * residue(__x));
            return *this;
        }
#ifdef __GNUC__
        else if constexpr (sizeof(value_type) <= 8U)
        {
            _M_value = static_cast<value_type>(residue(static_cast<__uint128_t>(_M_value) * residue(__x)));
            return *this;
        }
#endif
        else
        {
            __x = residue(__x);
    
            StaticModular result;
    
            for (; __x; *this += *this, __x >>= 1)
            {
                (__x & 1) ? void(result += *this) : void();
            }
    
            return *this = result;
        }
    }

    constexpr StaticModular& operator/=(value_type __x) noexcept
    { return *this = *this / __x; }

    constexpr StaticModular& operator%=(value_type __x) noexcept
    { return *this = *this % __x; }

    constexpr StaticModular operator<<(value_type __x) const noexcept
    { return *this * StaticModular(2).power(__x); }

    constexpr StaticModular operator>>(value_type __x) const noexcept
    { return *this / StaticModular(2).power(__x); }

    constexpr StaticModular& operator<<=(value_type __x) noexcept
    { return *this *= StaticModular(2).power(__x); }

    constexpr StaticModular& operator>>=(value_type __x) noexcept
    { return *this /= StaticModular(2).power(__x); }

    constexpr StaticModular operator^(value_type __x) const noexcept
    { return _M_value ^ __x; }

    constexpr StaticModular operator&(value_type __x) const noexcept
    { return _M_value & __x; }

    constexpr StaticModular operator|(value_type __x) const noexcept
    { return _M_value | __x; }

    constexpr StaticModular& operator^=(value_type __x) noexcept
    { return *this = *this ^ __x; }

    constexpr StaticModular& operator&=(value_type __x) noexcept
    { return *this = *this & __x; }

    constexpr StaticModular& operator|=(value_type __x) noexcept
    { return *this = *this | __x; }

    friend inline std::istream& operator>>(std::istream& __is, StaticModular& __that) noexcept
    { auto& result = __is >> __that._M_value; __that._M_value = __that.residue(__that._M_value); return result; }

    friend inline std::ostream& operator<<(std::ostream& __os, const StaticModular& __that) noexcept
    { return __os << __that._M_value; }

private:

    value_type _M_value;
};
}

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
        uint64 c;
        std::cin >> c;

        constexpr uint64 mod = 998244353;
        using mint64 = StaticModular<uint64, mod>;

        std::array<uint64, 7> p;

        for (int i = 0; i < 7; ++i)
        {
            std::cin >> p[i];
        }

        auto calc = [&](uint64 mark) -> std::pair<mint64, mint64>
        {
            std::pair<mint64, mint64> res{1, 1};

            for (uint64 i = 0; i < 7; ++i)
            {
                if (mark & (1 << i))
                {
                    res.first *= p[i];
                    res.second *= 100;
                }
                else
                {
                    res.first *= 100 - p[i];
                    res.second *= 100;
                }
            }

            return res;
        };

        std::array pcs{
            calc(0b1110111),
            calc(0b0100100),
            calc(0b1011101),
            calc(0b1101101),
            calc(0b0101110),
            calc(0b1101011),
            calc(0b1111011),
            calc(0b0100101),
            calc(0b1111111),
            calc(0b1101111)
        };

        mint64 ans;

        for (uint64 a = 0; a <= c; ++a)
        {
            const uint64 b = c - a;

            std::pair<mint64, mint64> sum{1, 1};

            for (uint64 i = 0, t = a; i < 4; ++i, t /= 10)
            {
                sum.first *= pcs[t % 10].first;
                sum.second *= pcs[t % 10].second;
            }
            
            for (uint64 i = 0, t = b; i < 4; ++i, t /= 10)
            {
                sum.first *= pcs[t % 10].first;
                sum.second *= pcs[t % 10].second;
            }

            ans += sum.first / sum.second;
        }

        std::cout << ans << '\n';
    }

    return 0;
}