/**
 * Codeforces Round 581 (Div. 2)
 *
 * => C. Anna, Svyatoslav and Maps ( @c 1700 )
 *
 * -> https://codeforces.com/contest/1204/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/1204/submission/387716055 By huanhuanonly
 *
 * @b Floyd–Warshall-algorithm
 * @b Linear-DP
 *
 * ----August 20, 2026 [01h:51m:24s]----
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

    int n;
    std::cin >> n;

    constexpr int inf = std::numeric_limits<int>::max() / 2;

    std::vector e(n + 1, std::vector<int>(n + 1));
    std::string s;

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> s;
        std::ranges::copy(s | std::views::transform([](char c) -> int { return std::array{inf, 1}[c - '0']; }), e[i].begin() + 1);
        e[i][i] = 0;
    }

    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                e[i][j] = std::min(e[i][j], e[i][k] + e[k][j]);
            }
        }
    }

    int m;
    std::cin >> m;

    std::vector<int> p(m);

    for (int i = 0; i < m; ++i)
    {
        std::cin >> p[i];
    }

    std::vector<int> dp(m, inf);
    dp.front() = 1;

    std::vector<int> pos(n + 1, ~0);
    std::vector<int> last(m);

    pos[p.front()] = 0;

    for (int i = 1; i < m; ++i)
    {
        for (int k = 1; k <= n; ++k)
        {
            if (~pos[k])
            {
                const int j = pos[k];

                if (e[p[j]][p[i]] == i - j)
                {
                    if (dp[j] + 1 < dp[i])
                    {
                        dp[i] = dp[j] + 1;
                        last[i] = j;
                    }
                }
            }
        }

        pos[p[i]] = i;
    }

    std::cout << dp.back() << '\n';

    std::vector<int> que;
    que.reserve(dp.back());

    for (int i = m - 1; i > 0; que.push_back(p[i]), i = last[i]);
    que.push_back(p.front());

    for (const int& i : que | std::views::reverse)
    {
        std::cout << i << ' ';
    }

    return 0;
}