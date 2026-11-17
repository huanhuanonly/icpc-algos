/**
 * Codeforces Round 1087 (Div. 2)
 *
 * => E. A Trivial String Problem ( @c 2200 )
 *
 * -> https://codeforces.com/contest/2209/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/2209/submission/370253169 By huanhuanonly
 *
 * @b Knuth-Morris-Pratt and @b Linear-DP
 *
 * ----April 08, 2026 [17h:05m:14s]----
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
    inline namespace string
{
class Kmp
{
public:

    using value_type = std::string::value_type;
    using size_type = int;

    static constexpr size_type npos = size_type(-1);

    Kmp() noexcept = default;

    Kmp(std::string __pattern)
        : _M_pattern(std::move(__pattern)), _M_lps(_M_pattern.size())
    { _M_build(); }

    [[nodiscard]] size_type
    size() const noexcept
    { return static_cast<size_type>(_M_pattern.size()); }

    [[nodiscard]] bool
    empty() const noexcept
    { return size() == 0; }

    [[nodiscard]] size_type
    longest_prefix_suffix(size_type __i) const noexcept
    { return _M_lps[__i]; }

    [[nodiscard]] size_type
    lps(size_type __i) const noexcept
    { return _M_lps[__i]; }

    [[nodiscard]] std::string_view
    pattern() const noexcept
    { return _M_pattern; }

    [[nodiscard]] size_type
    find(std::string_view __s) const
    {
        if (empty())
        {
            return 0;
        }

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                return i + 1 - size();
            }
        }

        return npos;
    }

    template<std::output_iterator<size_type> _Out>
    _Out
    find_all(std::string_view __s, _Out __result) const
    {
        if (empty())
        {
            return std::ranges::copy(std::views::iota(size_type(0), size_type(__s.size() + 1)), __result).out;
        }

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                *__result = i + 1 - size();
                ++__result;
                c = _M_lps[c - 1];
            }
        }

        return __result;
    }

#if __has_include(<generator>) && defined(__cpp_lib_generator)
    [[nodiscard]] std::generator<size_type>
    find_all(std::string_view __s) const
    {
        if (empty())
        {
            for (size_type i = 0; i <= size_type(__s.size()); ++i)
            {
                co_yield i;
            }

            co_return;
        }

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                co_yield i + 1 - size();
                c = _M_lps[c - 1];
            }
        }
    }
#endif

    [[nodiscard]] bool
    contains(std::string_view __s) const
    { return find(__s) != npos; }

    [[nodiscard]] size_type
    count_matches(std::string_view __s) const
    {
        if (empty())
        {
            return size_type(__s.size() + 1);
        }

        size_type cnt = 0;

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                ++cnt;
                c = _M_lps[c - 1];
            }
        }

        return cnt;
    }

private:

    void
    _M_build()
    {
        for (size_type i = 1; i < size(); ++i)
        {
            size_type len = _M_lps[i - 1];

            while (len > 0 and _M_pattern[len] != _M_pattern[i])
            {
                len = _M_lps[len - 1];
            }

            if (_M_pattern[len] == _M_pattern[i])
            {
                ++len;
            }

            _M_lps[i] = len;
        }
    }

private:

    std::string _M_pattern;
    std::vector<size_type> _M_lps;
};
}} // namespace huanhuanonly::string

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
        int n, q;
        std::cin >> n >> q;

        std::string s;
        std::cin >> s;

        while (q--)
        {
            int l, r;
            std::cin >> l >> r;

            --l, --r;

            Kmp kmp(s.substr(l, r - l + 1));

            std::vector<int> b(kmp.size());

            for (int i = 1; i < kmp.size(); ++i)
            {
                if (const auto t = kmp.longest_prefix_suffix(i))
                {
                    if (kmp.longest_prefix_suffix(t - 1) == 0)
                    {
                        b[i] = t;
                    }
                    else
                    {
                        b[i] = b[t - 1];
                    }
                }
            }

            std::vector<int> dp(kmp.size());
            dp[0] = 1;

            uint64 sum = dp[0];

            for (int i = 1; i < kmp.size(); ++i)
            {
                sum += dp[i] = dp[i - b[i]] + 1;
            }

            std::cout << sum << '\n';
        }
    }

    return 0;
}