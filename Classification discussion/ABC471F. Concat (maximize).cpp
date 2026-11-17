/**
 * AtCoder Beginner Contest 471
 *
 * => F - Concat (maximize) ( @c 550 )
 *
 * -> https://atcoder.jp/contests/abc471/tasks/abc471_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc471/submissions/78476511 By huanhuanonly
 *
 * @b Classification-discussion
 * @b Greedy
 *
 * ----August 17, 2026 [02h:54m:19s]----
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, k;
    std::cin >> n >> k;

    std::vector<std::string> v(n);

    for (auto& i : v)
    {
        std::cin >> i;
    }

    static auto $ = [](const std::string& s) -> std::string_view
    {
        if (const auto offset = s.find_first_not_of('0'); ~offset)
        {
            return std::string_view(s.begin() + offset, s.end());
        }
        else
        {
            return std::string_view{};
        }
    };

    static auto comp = [](const auto& lhs, const auto& rhs) -> bool
    {
        if (lhs.size() != rhs.size())
        {
            return lhs.size() > rhs.size();
        }
        else
        {
            return lhs > rhs;
        }
    };

    std::string ans1, ans2;

    {
        std::ranges::sort(v, comp);
        std::ranges::sort(v | std::views::take(k), [](const std::string& lhs, const std::string& rhs) -> bool
        {
            return lhs + rhs > rhs + lhs;
        });

        for (const auto& i : v | std::views::take(k))
        {
            ans1.append(i);
        }

        ans1 = $(ans1);

        if (ans1.empty())
        {
            ans1.push_back('0');
        }
    }

    {
        std::ranges::sort(v, comp);
        std::ranges::sort(v | std::views::take(k - 1), [](const std::string& lhs, const std::string& rhs) -> bool
        {
            return lhs + rhs > rhs + lhs;
        });
        std::swap(v[k - 1], *std::ranges::min_element(v | std::views::drop(k - 1), comp, $));

        ans2 = v[k - 1];

        for (const auto& i : v | std::views::take(k - 1))
        {
            ans2.append(i);
        }

        ans2 = $(ans2);

        if (ans2.empty())
        {
            ans2.push_back('0');
        }
    }

    std::cout << std::min(ans1, ans2, comp) << '\n';

    return 0;
}