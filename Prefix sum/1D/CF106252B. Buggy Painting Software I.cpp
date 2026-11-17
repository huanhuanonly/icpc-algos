/**
 * The 2025 ICPC Asia Shenyang Regional Contest (The 4th Universal Cup. Stage 6: Grand Prix of Shenyang)
 *
 * => B. Buggy Painting Software I
 *
 * -> https://codeforces.com/gym/106252/problem/B
 *
 * Submissions ~> https://codeforces.com/gym/106252/submission/389373050 By huanhuanonly
 *
 * @b Prefix-sum
 *
 * ----September 04, 2026 [22h:55m:04s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int64 n, m, a, b;
        std::cin >> n >> m >> a >> b;

        std::map<int64, int64> map;

        for (int i = 0, v; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                std::cin >> v;
                ++map[v];
            }
        }

        map[0];

        const auto cnt0 = map.extract(0).mapped();
        auto cnt = map | std::views::values | std::ranges::to<std::vector>();

        std::ranges::sort(cnt);
        cnt.push_back(0);

        auto suf = cnt;

        for (int i = int(suf.size()) - 2, j = 0; i >= 0; --i, ++j)
        {
            suf[i] *= j;
        }

        std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
        std::partial_sum(suf.rbegin(), suf.rend(), suf.rbegin());

        int64 min = (suf[0] * b) + (cnt0 * (suf.size() - 1) * b);

        for (int i = 0; i < cnt.size() - 1; ++i)
        {
            min = std::min(min, cnt[i] * a + (suf[i + 1] * b) + (cnt0 * int64(suf.size() - i - 2) * b));
        }

        std::cout << min << '\n';
    }

    return 0;
}