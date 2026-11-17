/**
 * Next DP Contest
 *
 * => C - String ( @c 2 )
 *
 * -> https://atcoder.jp/contests/ndpc/tasks/ndpc2026_c
 *
 * Submissions ~> https://atcoder.jp/contests/ndpc/submissions/78930449 By huanhuanonly
 *
 * @b Counting-DP
 *
 * ----September 04, 2026 [09h:01m:25s]----
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

    std::string a, b, c;
    std::cin >> a >> b >> c;

    constexpr uint64 mod = 998244353;

    std::vector dp(n + 1, std::vector(a.size() + 1, std::vector(b.size() + 1, std::vector(c.size() + 1, uint64{}))));
    dp[0][0][0][0] = 1;

    for (int i = 0; i < n; ++i)
    {
        for (int x = 0; x < a.size(); ++x)
        {
            for (int y = 0; y < b.size(); ++y)
            {
                for (int z = 0; z < c.size(); ++z)
                {
                    for (char ch = 'a'; ch <= 'z'; ++ch)
                    {
                        (dp[i + 1][x + (ch == a[x])][y + (ch == b[y])][z + (ch == c[z])] += dp[i][x][y][z]) %= mod;
                    }
                }
            }
        }
    }

    uint64 sum = 0;

    for (int x = 0; x < a.size(); ++x)
    {
        for (int y = 0; y < b.size(); ++y)
        {
            for (int z = 0; z < c.size(); ++z)
            {
                sum += dp.back()[x][y][z];
                sum %= mod;
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}