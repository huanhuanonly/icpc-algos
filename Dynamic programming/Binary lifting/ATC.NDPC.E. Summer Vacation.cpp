/**
 * Next DP Contest
 *
 * => E - Summer Vacation ( @c 3 )
 *
 * -> https://atcoder.jp/contests/ndpc/tasks/ndpc2026_e
 *
 * Submissions ~> https://atcoder.jp/contests/ndpc/submissions/78955962 By huanhuanonly
 *
 * @b Binary-lifting
 *
 * ----September 05, 2026 [15h:27m:06s]----
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

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> min(n + 3, n + 2);

    for (int i = 0; i < m; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        min[l] = std::min(min[l], r + 1);
    }

    std::partial_sum(min.rbegin(), min.rend(), min.rbegin(), std::ranges::min);

    constexpr int laycnt = 20;
    std::vector<std::array<int, laycnt>> dp(n + 3);

    std::ranges::copy(min, (dp | std::views::elements<0>).begin());

    for (int lay = 1; lay < laycnt; ++lay)
    {
        for (int i = 1; i <= n + 2; ++i)
        {
            dp[i][lay] = dp[dp[i][lay - 1]][lay - 1];
        }
    }

    while (q--)
    {
        int l, r;
        std::cin >> l >> r;

        int cnt = 0;

        for (int lay = laycnt - 1; lay >= 0; --lay)
        {
            if (dp[l][lay] <= r + 1)
            {
                l = dp[l][lay];
                cnt += 1 << lay;
            }
        }

        std::cout << cnt << '\n';
    }

    return 0;
}