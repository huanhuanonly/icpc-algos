/**
 * AtCoder Beginner Contest 461
 *
 * => D - Count Subgrid Sum = K ( @c 425 )
 *
 * -> https://atcoder.jp/contests/abc461/tasks/abc461_d
 *
 * Submissions ~> https://atcoder.jp/contests/abc461/submissions/76480793 By huanhuanonly
 *
 * @b Prefix-sum
 *
 * ----June 06, 2026 [21h:32m:21s]----
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

    int h, w, k;
    std::cin >> h >> w >> k;

    std::vector v(h + 1, std::vector(w + 1, 0));

    for (int i = 1; i <= h; ++i)
    {
        for (int j = 1; j <= w; ++j)
        {
            char c;
            std::cin >> c;

            v[i][j] = c - '0';
        }
    }

    std::vector<int> cnt(h * w + 1);

    int64 ans = 0;

    for (int lo = 1; lo <= h; ++lo)
    {
        std::vector<int> pre(w + 1);

        for (int hi = lo; hi <= h; ++hi)
        {
            for (int i = 1; i <= w; ++i)
            {
                pre[i] += v[hi][i];
            }

            auto presum = pre;
            std::partial_sum(pre.begin(), pre.end(), presum.begin());

            for (int i = 0; i <= w; ++i)
            {
                if (presum[i] >= k)
                {
                    ans += cnt[presum[i] - k];
                }

                ++cnt[presum[i]];
            }

            for (int i = 0; i <= w; ++i)
            {
                --cnt[presum[i]];
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}