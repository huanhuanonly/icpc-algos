/**
 * KEYENCE Programming Contest 2023 Summer（AtCoder Beginner Contest 315）
 *
 * => F - Shortcuts ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc315/tasks/abc315_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc315/submissions/76348284 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----June 02, 2026 [17h:52m:34s]----
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

real80 distance(const std::pair<int, int>& s, const std::pair<int, int>& t)
{
    return std::sqrt(real80((s.first - t.first) * (s.first - t.first) + (s.second - t.second) * (s.second - t.second)));
}

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

    std::vector<std::pair<int, int>> v(n);

    for (auto& [x, y] : v)
    {
        std::cin >> x >> y;
    }

    std::vector<std::array<real80, 30>> dp(n);

    for (int c = 0; c < 30; ++c)
    {
        for (int i = 1; i < n; ++i)
        {
            dp[i][c] = dp[i - 1][c] + distance(v[i - 1], v[i]);

            for (int j = 1; j <= c and i - j - 1 >= 0; ++j)
            {
                dp[i][c] = std::min(dp[i][c], dp[i - j - 1][c - j] + distance(v[i - j - 1], v[i]));
            }
        }
    }

    auto min = 1e18L;

    for (int c = 0; c < 30; ++c)
    {
        min = std::min(min, dp.back()[c] + (c ? 1ULL << c - 1 : 0));
    }

    std::cout << std::fixed << std::setprecision(12) << min << '\n';

    return 0;
}