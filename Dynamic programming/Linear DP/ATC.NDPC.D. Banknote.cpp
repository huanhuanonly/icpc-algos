/**
 * Next DP Contest
 *
 * => D - Banknote ( @c 3 )
 *
 * -> https://atcoder.jp/contests/ndpc/tasks/ndpc2026_d
 *
 * Submissions ~> https://atcoder.jp/contests/ndpc/submissions/78931721 By huanhuanonly
 *
 * @b Linear-DP
 *
 * ----September 04, 2026 [10h:36m:59s]----
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
        std::string n;
        std::cin >> n;

        constexpr auto inf = std::numeric_limits<int>::max() / 2;

        std::vector dp(n.size(), std::array<int, 2>{});

        dp.back() = {n.back() - '0', 10 - n.back() + '0'};

        for (int i = static_cast<int>(dp.size()) - 2; i >= 0; --i)
        {
            dp[i][0] = std::min((n[i] - '0') + dp[i + 1][0], (n[i] - '0' + 1) + dp[i + 1][1]);
            dp[i][1] = std::min((10 - (n[i] - '0')) + dp[i + 1][0], (10 - (n[i] - '0' + 1)) + dp[i + 1][1]);
        }

        std::cout << std::min(dp.front().front(), dp.front().back() + 1) << '\n';
    }

    return 0;
}