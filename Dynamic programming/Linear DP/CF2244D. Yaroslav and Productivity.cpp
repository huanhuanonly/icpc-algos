/**
 * Codeforces Round 1109 (Div. 3)
 *
 * => D. Yaroslav and Productivity ( @c 1200 )
 *
 * -> https://codeforces.com/contest/2244/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2244/submission/382622932 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----July 14, 2026 [23h:17m:08s]----
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
        int n, m;
        std::cin >> n >> m;

        std::vector<int64> add(n + 1), sub(n + 1);

        for (int i = 1, v; i <= n; ++i)
        {
            std::cin >> v;

            add[i] = add[i - 1];
            sub[i] = sub[i - 1];

            if (v >= 0)
            {
                add[i] += v;
            }
            else
            {
                sub[i] -= v;
            }
        }

        std::vector<int> b(m);

        for (int& i : b)
        {
            std::cin >> i;
        }

        b.push_back(0);
        std::ranges::sort(b);
        b.push_back(n + 1);

        int cpos = 1;

        std::vector<int64> dp(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + ((add[i] - add[i - 1]) - (sub[i] - sub[i - 1]));

            if (b[cpos] == i)
            {
                dp[i] = std::max(dp[i], dp[b[cpos - 1]] + ((sub[i] - sub[b[cpos - 1]]) - (add[i] - add[b[cpos - 1]])));
                ++cpos;
            }
        }

        std::cout << dp.back() << '\n';
    }

    return 0;
}