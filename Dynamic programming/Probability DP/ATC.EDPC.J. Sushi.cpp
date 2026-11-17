/**
 * Educational DP Contest
 * 
 * => J - Sushi ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_j
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/74986441 By huanhuanonly
 * 
 * @b Expectation-DP and @b Dfs
 * 
 * ----April 16, 2026 [00h:51m:59s]----
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
    
    std::array<int, 4> cnt{};

    for (int i = 0, v; i < n; ++i)
    {
        std::cin >> v;
        ++cnt[v];
    }

    std::vector dp(n + 1, std::vector(n + 1, std::vector(n + 1, real80{-1})));
    dp[n][0][0] = 0;

    auto dfs = [&, n = real80(n)](const auto& self, real80 a, real80 b, real80 c) -> real80
    {
        const real80 d = n - a - b - c;

        if (a < 0 or b < 0 or c < 0 or d < 0)
        {
            return 0;
        }

        if (dp[a][b][c] != -1)
        {
            return dp[a][b][c];
        }

        return dp[a][b][c] = (1 + b / n * self(self, a + 1, b - 1, c) + c / n * self(self, a, b + 1, c - 1) + d / n * self(self, a, b, c + 1)) / (1 - a / n);
    };

    std::cout << std::fixed << std::setprecision(12) << dfs(dfs, cnt[0], cnt[1], cnt[2]);

    return 0;
}