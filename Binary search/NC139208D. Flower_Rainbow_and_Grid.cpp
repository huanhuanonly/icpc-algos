/**
 * 牛客小白月赛136
 *
 * => D-Flower_Rainbow_and_Grid ( @c 1500 )
 *
 * -> https://ac.nowcoder.com/acm/contest/139208/D
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84602902 By huanhuanonly
 *
 * @b Binary-search
 * @b Prefix-sum
 *
 * ----August 26, 2026 [00h:09m:21s]----
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

    std::vector<int64> pre(5e4 + 1);

    for (int64 i = 1; i < pre.size(); ++i)
    {
        pre[i] += pre[i - 1] + i * i;
    }

    int _;
    std::cin >> _;

    while (_--)
    {
        int64 n, m, k;
        std::cin >> n >> m >> k;

        auto calc = [&](int64 x) -> std::pair<int64, int64>
        {
            int64 cnt = 0;
            int64 sum = 0;

            for (int64 i = 1; i <= n; ++i)
            {
                if (i * i <= x)
                {
                    continue;
                }

                const int64 j = std::min(m, static_cast<int64>(std::sqrt(i * i - x)));

                cnt += j;
                sum += i * i * j - pre[j];
            }

            return {cnt, sum};
        };

        int64 l = -m * m, r = n * n, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (calc(mid).first >= k)
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }

        const auto [cnt, sum] = calc(l);
        std::cout << sum - (cnt - k) * l << '\n';
    }

    return 0;
}