/**
 * 第十二届中国大学生程序设计竞赛 乐山站（CCPC 2026 Leshan Site）
 *
 * => L. 交换字母
 *
 * -> https://qoj.ac/contest/4685/problem/24852
 *
 * Submissions ~> https://qoj.ac/submission/3423368 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----November 10, 2026 [17h:16m:22s]----
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

void chmax(auto& lhs, const auto& rhs)
{
    if (lhs < rhs)
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::string s;
        std::cin >> s;

        std::vector dp(n, std::vector(26, std::numeric_limits<int>::min() / 2));
        dp[0][s.front() - 'a'] = 0;

        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < 26; ++j)
            {
                chmax(dp[i][s[i] - 'a'], dp[i - 1][j] + (s[i] == 'a' + j));
            }

            if (i >= 2)
            {
                for (int j = 0; j < 26; ++j)
                {
                    chmax(dp[i][s[i - 1] - 'a'], dp[i - 2][j] + (s[i] == 'a' + j) + (s[i] == s[i - 1]));
                }
            }
            else
            {
                chmax(dp[i][s[i - 1] - 'a'], 0);
            }
        }

        std::cout << std::ranges::max(dp.back()) << '\n';
    }

    return 0;
}