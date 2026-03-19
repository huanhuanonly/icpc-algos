/**
 * 牛客小白月赛128
 * 
 * => D-进退的艺术 ( @c 1300 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/127265/D
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=81842672 By huanhuanonly
 * 
 * @b Prefix-sum and @b Binary-search
 * 
 * ----January 30, 2026 [22h:06m:28s]----
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
        int64 n, m;
        std::cin >> n >> m;

        std::vector<std::pair<int64, int64>> v(n + 1);
        std::vector<int64> pre(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i].first;
            v[i].second = i;

            pre[i] = v[i].first;
        }

        std::ranges::sort(v);
        std::ranges::sort(pre);

        std::partial_sum(pre.begin(), pre.end(), pre.begin());

        auto sum = [&](int64 l, int64 r, int64 e) -> int64
        {
            int64 s = pre[r] - pre[l - 1];

            if (l <= e and e <= r)
            {
                s -= v[e].first;
            }

            return s;
        };

        std::vector<int64> ans(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            const int64 mid = std::ranges::upper_bound(v, m - v[i].first, {}, &std::pair<int64, int64>::first) - v.begin();

            ans[v[i].second] += (mid - 1 - (i < mid)) * v[i].first;

            if (mid <= n)
            {
                ans[v[i].second] -= sum(mid, n, i);
            }
        }

        for (int i = 1; i <= n; ++i)
        {
            std::cout << ans[i] << " \n"[i == n];
        }
    }

    return 0;
}