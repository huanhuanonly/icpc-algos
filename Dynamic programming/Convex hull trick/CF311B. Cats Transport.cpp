/**
 * Codeforces Round 185 (Div. 1)
 *
 * => B. Cats Transport ( @c 2400 )
 *
 * -> https://codeforces.com/contest/311/problem/B
 *
 * Submissions ~> https://codeforces.com/contest/311/submission/348450801 By huanhuanonly
 *
 * @b DP with @b Convex-hull-trick
 * @b Prefix-sum
 * @b Monotonic-queue
 *
 * ----November 11, 2025 [17h:52m:06s]----
*/

/**
 * @see the original solution https://codeforces.com/contest/311/submission/347631999 in O(pm^2)
 *      without any optimizations.
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m, p;
    std::cin >> n >> m >> p;

    std::vector<int64> offset(n + 1);

    for (int i = 2, d; i <= n; ++i)
    {
        std::cin >> d;
        offset[i] = offset[i - 1] - d;
    }

    std::vector<int64> v(m + 1);

    for (int i = 1, h, t; i <= m; ++i)
    {
        std::cin >> h >> t;
        v[i] = t + offset[h];
    }

    std::ranges::sort(v | std::views::drop(1));

    auto s = v;
    std::partial_sum(v.begin(), v.end(), s.begin());

    constexpr auto inf = std::numeric_limits<int64>::max() / 2;

    std::vector dp(p + 1, std::vector(m + 1, inf));

    for (int i = 0; i <= p; ++i)
    {
        dp[i][0] = 0;
    }

    struct point
    {
        int64 x, y;

        point operator-(const point& other) const noexcept
        {
            return {x - other.x, y - other.y};
        }

        int64 operator*(const point& other) const noexcept
        {
            return (x * other.y) - (y * other.x);
        }
    };

    for (int i = 1; i <= p; ++i)
    {
        std::vector<point> ps(m + 1);

        for (int64 k = 0; k < m; ++k)
        {
            ps[k] = {k, dp[i - 1][k] != inf ? s[k] + dp[i - 1][k] : inf};
        }

        std::deque<point> lines;

        lines.push_back(ps[0]);

        for (int j = 1; j <= m; ++j)
        {
            auto $ = [&](const point& c) -> int64
            {
                return (c.y - v[j] * c.x) - s[j] + j * v[j];
            };

            for (; lines.size() >= 2 and $(lines[0]) >= $(lines[1]); lines.pop_front());

            dp[i][j] = $(lines.front());

            if (ps[j].y != inf)
            {
                for (; lines.size() >= 2 and (lines[lines.size() - 2] - lines.back()) * (ps[j] - lines.back()) > 0; lines.pop_back());

                lines.push_back(ps[j]);
            }
        }
    }

    auto ans = inf;

    for (int i = 1; i <= p; ++i)
    {
        ans = std::min(ans, dp[p].back());
    }

    std::cout << ans;

    return 0;
}