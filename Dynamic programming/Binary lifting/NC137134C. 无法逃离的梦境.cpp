/**
 * 第六届上海理工大学ACM程序设计全国挑战赛
 *
 * => C-无法逃离的梦境
 *
 * -> https://ac.nowcoder.com/acm/contest/137134/C
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84065415 By huanhuanonly
 *
 * @b Binary-lifting
 *
 * ----July 18, 2026 [13h:22m:27s]----
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

void chmin(auto& lhs, const auto& rhs)
{
    if (rhs < lhs)
    {
        lhs = rhs;
    }
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, c, q;
    std::cin >> n >> c >> q;

    constexpr int laycnt = 30;
    std::vector<std::array<int, laycnt>> p(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> p[i][0];
    }

    constexpr int maxc = 5;

    constexpr auto inf = std::numeric_limits<int64>::max() / 2;
    std::vector dp(n + 1, std::vector(laycnt, std::array<std::array<int64, maxc>, maxc>{}));

    for (int i = 1; i <= n; ++i)
    {
        for (int a = 0; a < c; ++a)
        {
            for (int b = 0; b < c; ++b)
            {
                std::cin >> dp[i][0][a][b];
            }
        }
    }

    for (int lay = 1; lay < laycnt; ++lay)
    {
        for (int i = 1; i <= n; ++i)
        {
            p[i][lay] = p[p[i][lay - 1]][lay - 1];

            for (int a = 0; a < c; ++a)
            {
                for (int b = 0; b < c; ++b)
                {
                    dp[i][lay][a][b] = inf;

                    for (int k = 0; k < c; ++k)
                    {
                        chmin(dp[i][lay][a][b], dp[i][lay - 1][a][k] + dp[p[i][lay - 1]][lay - 1][k][b]);
                    }
                }
            }
        }
    }

    while (q--)
    {
        int x, k, s, t;
        std::cin >> x >> k >> s >> t;

        auto min = dp[x][0][s];

        x = p[x][0];
        --k;

        for (int i = 0; i < laycnt; ++i)
        {
            if (k & 1 << i)
            {
                auto cmin = std::array<int64, maxc>{inf, inf, inf, inf, inf};

                for (int a = 0; a < c; ++a)
                {
                    for (int b = 0; b < c; ++b)
                    {
                        chmin(cmin[b], min[a] + dp[x][i][a][b]);
                    }
                }

                min = std::move(cmin);
                x = p[x][i];
            }
        }

        std::cout << min[t] << '\n';
    }

    return 0;
}