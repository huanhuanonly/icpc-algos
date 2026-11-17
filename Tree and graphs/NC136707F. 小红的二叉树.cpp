/**
 * 牛客周赛 Round 148
 *
 * => F-小红的二叉树 ( @c 1900 )
 *
 * -> https://ac.nowcoder.com/acm/contest/136707/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83870006 By huanhuanonly
 *
 * @b Trees
 *
 * ----June 15, 2026 [08h:50m:51s]----
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

    uint64 n, x;
    std::cin >> n >> x;

    uint64 ans = 1;

    auto count = [&](uint64 u) -> std::vector<uint64>
    {
        std::vector<uint64> cnt{1};

        uint64 l = u, r = u;

        while (true)
        {
            l <<= 1;
            r = std::min(r << 1 | 1, n);

            if (l > n)
            {
                break;
            }

            cnt.push_back(r - l + 1);

            if (r == n)
            {
                break;
            }
        }

        return cnt;
    };

    if (x * 2 + 1 <= n)
    {
        ans += *std::ranges::fold_left_first(
            std::views::zip_transform(
                [](uint64 lc, uint64 rc) -> uint64 { return lc * rc; },
                count(x << 1),
                count(x << 1 | 1)),
            std::plus{});
    }

    if (x != 1)
    {
        const auto& curcnt = count(x);

        for (int i = 1; i < curcnt.size() and x != 1; ++i, x >>= 1)
        {
            auto&& facnt = count(x ^ 1);
            facnt.insert(facnt.begin(), 1);

            for (int j = 0; i + j < curcnt.size() and j < facnt.size(); ++j)
            {
                ans += curcnt[i + j] * facnt[j];
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}