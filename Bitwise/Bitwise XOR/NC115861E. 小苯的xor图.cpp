/**
 * 牛客周赛 Round 105
 * 
 * => E-小苯的xor图 ( @c 1500 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/115861/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78901670 By huanhuanonly
 * 
 * @b Bitwise-XOR
 * 
 * ----August 17, 2025 [21h:33m:54s]----
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

inline namespace huanhuanonly
{
template<std::integral _Tp, _Tp _Modulus>
class Modular
{
public:

    using value_type = _Tp;
    using reference = _Tp&;
    using const_reference = const _Tp&;

    constexpr Modular(value_type __value = {}) noexcept
        : _M_value(residue(__value))
    { }

    constexpr value_type value() const noexcept
    { return _M_value; }

    static constexpr value_type modulus() noexcept
    { return _Modulus; }

    static constexpr value_type residue(value_type __x) noexcept
    {
        if constexpr (std::is_unsigned_v<value_type>)
        {
            return __x % modulus();
        }
        else
        {
            return (__x % modulus() + modulus()) % modulus();
        }
    }

    constexpr Modular power(value_type __x) const noexcept
    {
        Modular result(static_cast<value_type>(1));
        auto t = *this;

        for (; __x; t *= t, __x >>= 1)
        {
            (__x & 1) ? void(result *= t) : void();
        }

        return result;
    }

    constexpr Modular inverse() const noexcept
    {
        static_assert (modulus() > 2);
        return power(modulus() - 2);
    }

    template<typename _Ty>
    constexpr _Ty cast() const noexcept
    { return static_cast<_Ty>(_M_value); }


    constexpr Modular& operator=(value_type __value) noexcept
    { _M_value = residue(__value); return *this; }

    constexpr operator bool() const noexcept
    { return static_cast<bool>(_M_value); }

    constexpr operator value_type() const noexcept
    { return _M_value; }

    constexpr std::strong_ordering operator<=>(value_type __x) const noexcept
    { return _M_value <=> __x; }

    constexpr std::strong_ordering operator<=>(Modular __other) const noexcept
    { return _M_value <=> __other._M_value; }

    constexpr reference operator*() noexcept
    { return _M_value; }
    
    constexpr const_reference operator*() const noexcept
    { return _M_value; }

    constexpr bool operator!() const noexcept
    { return !_M_value; }

    constexpr Modular operator~() const noexcept
    { return ~_M_value; }

    constexpr Modular operator+() const noexcept
    { return +_M_value; }

    constexpr Modular operator-() const noexcept
    { return -_M_value; }

    constexpr Modular& operator++() noexcept
    { _M_value = residue(++_M_value); return *this; }

    constexpr Modular& operator--() noexcept
    { _M_value = residue(--_M_value); return *this; }

    constexpr Modular operator++(int) noexcept
    { auto t = *this; ++*this; return t; }

    constexpr Modular operator--(int) noexcept
    { auto t = *this; --*this; return t; }

    constexpr Modular operator+(value_type __x) const noexcept
    { return _M_value + residue(__x); }

    constexpr Modular operator-(value_type __x) const noexcept
    { return _M_value - residue(__x); }
    
    constexpr Modular operator*(value_type __x) const noexcept
    { auto t = *this; t *= __x; return t; }

    constexpr Modular operator/(value_type __x) const noexcept
    { return *this * Modular(__x).inverse(); }

    constexpr Modular operator%(value_type __x) const noexcept
    { return _M_value % __x; }

    constexpr Modular& operator+=(value_type __x) noexcept
    { return *this = *this + __x; }
    
    constexpr Modular& operator-=(value_type __x) noexcept
    { return *this = *this - __x; }

    constexpr Modular& operator*=(value_type __x) noexcept
    {
        if constexpr (std::numeric_limits<value_type>::max() / modulus() >= modulus())
        {
            _M_value = residue(_M_value * residue(__x));
            return *this;
        }
        else
        {
            __x = residue(__x);
    
            Modular result;
    
            for (; __x; *this += *this, __x >>= 1)
            {
                (__x & 1) ? void(result += *this) : void();
            }
    
            return *this = result;
        }
    }

    constexpr Modular& operator/=(value_type __x) noexcept
    { return *this = *this / __x; }

    constexpr Modular& operator%=(value_type __x) noexcept
    { return *this = *this % __x; }

    constexpr Modular operator<<(value_type __x) const noexcept
    { return *this * Modular(2).power(__x); }

    constexpr Modular operator>>(value_type __x) const noexcept
    { return *this / Modular(2).power(__x); }

    constexpr Modular& operator<<=(value_type __x) noexcept
    { return *this *= Modular(2).power(__x); }

    constexpr Modular& operator>>=(value_type __x) noexcept
    { return *this /= Modular(2).power(__x); }

    constexpr Modular operator^(value_type __x) const noexcept
    { return _M_value ^ __x; }

    constexpr Modular operator&(value_type __x) const noexcept
    { return _M_value & __x; }

    constexpr Modular operator|(value_type __x) const noexcept
    { return _M_value | __x; }

    constexpr Modular& operator^=(value_type __x) noexcept
    { return *this = *this ^ __x; }

    constexpr Modular& operator&=(value_type __x) noexcept
    { return *this = *this & __x; }

    constexpr Modular& operator|=(value_type __x) noexcept
    { return *this = *this | __x; }

    friend inline std::istream& operator>>(std::istream& __is, Modular& __that) noexcept
    { auto& result = __is >> __that._M_value; __that._M_value = __that.residue(__that._M_value); return result; }

    friend inline std::ostream& operator<<(std::ostream& __os, const Modular& __that) noexcept
    { return __os << __that._M_value; }

private:

    value_type _M_value;
};
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

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

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    using bc = std::array<int, 31>;
    using mint = Modular<uint64, 998244353>;

    mint ans = 0;

    for (int point = 1; point <= n; ++point)
    {
        bc cnt{};

        for (int i : e[point])
        {
            std::bitset<31> bs(v[i] ^ v[point]);

            for (int j = 0; j < bs.size(); ++j)
            {
                if (bs[j])
                {
                    ++cnt[j];
                }
            }
        }

        uint64 num = 1;
        for (int i : e[point])
        {
            std::bitset<31> bs(v[i] ^ v[point]);

            for (uint64 j = 0; j < bs.size(); ++j)
            {
                if (bs[j])
                {
                    --cnt[j];
                }
            }

            bs = std::bitset<31>(v[i]);

            for (uint64 j = 0, cur = 1; j < bs.size(); ++j, cur <<= 1)
            {
                if (bs[j])
                {
                    ans += (e[point].size() - num - cnt[j]) * cur;
                }
                else
                {
                    ans += cnt[j] * cur;
                }
            }

            ++num;
        }
    }

    std::cout << ans;

    return 0;
}