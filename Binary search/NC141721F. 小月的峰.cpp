/**
 * 牛客周赛 Round 165
 *
 * => F-小月的峰 ( @c 1800 )
 *
 * -> https://ac.nowcoder.com/acm/contest/141721/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84986896 By huanhuanonly
 *
 * @b Binary-search
 *
 * ----October 11, 2026 [20h:59m:54s]----
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

    std::vector<int64> l(n), r(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> l[i] >> r[i];
    }

    auto check = [&](int64 mid) -> bool
    {
        std::vector<int64> pl(n), pr(n);
        std::vector<bool> pv(n);

        pl[0] = l[0], pr[0] = r[0];
        pv[0] = true;

        for (int i = 1; i < n; ++i)
        {
            if (pv[i - 1])
            {
                pl[i] = std::max(l[i], pl[i - 1] + 1);
                pr[i] = std::min(r[i], pr[i - 1] + mid);
                pv[i] = pl[i] <= pr[i];
            }
        }

        std::vector<int64> sl(n), sr(n);
        std::vector<bool> sv(n);

        sl.back() = l.back(), sr.back() = r.back();
        sv.back() = true;

        for (int i = n - 2; i >= 0; --i)
        {
            if (sv[i + 1])
            {
                sl[i] = std::max(l[i], sl[i + 1] + 1);
                sr[i] = std::min(r[i], sr[i + 1] + mid);
                sv[i] = sl[i] <= sr[i];
            }
        }

        for (int i = 1; i <= n - 2; ++i)
        {
            if (pv[i] and sv[i])
            {
                if (std::max(pl[i], sl[i]) <= std::min(pr[i], sr[i]))
                {
                    return true;
                }
            }
        }

        return false;
    };

    int64 lo = 0, hi = 2e9 + 10;

    while (hi - lo > 1)
    {
        const auto mid = lo + hi >> 1;

        if (check(mid))
        {
            hi = mid;
        }
        else
        {
            lo = mid;
        }
    }

    if (check(hi))
    {
        std::cout << hi << '\n';
    }
    else
    {
        std::cout << "-1\n";
    }

    return 0;
}