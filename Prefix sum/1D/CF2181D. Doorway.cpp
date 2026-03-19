/**
 * 2025-2026 ICPC, NERC, Northern Eurasia Finals (Unrated, Online Mirror, ICPC Rules, Teams Preferred)
 * 
 * => D. Doorway ( @c 2000 )
 * 
 * -> https://codeforces.com/contest/2181/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/2181/submission/356632794 By huanhuanonly
 * 
 * @b Prefix-sum
 * 
 * ----January 06, 2026 [22h:07m:14s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int64 n;
    std::cin >> n;

    std::vector<std::tuple<int64, int64, int64>> v;
    int64 maxl = 0;

    for (int64 i = 0; i < n; ++i)
    {
        int64 k;
        std::cin >> k;
        
        std::vector<int64> l(k + 2);

        std::cin >> l[0] >> l[k + 1];

        for (int64 j = 1; j <= k; ++j)
        {
            std::cin >> l[j];
        }

        auto r = l;

        maxl = std::max(maxl, l[0]);

        for (int64 j = 1; j <= k; ++j)
        {
            l[j] += l[j - 1];
        }

        for (int64 j = k; j >= 1; --j)
        {
            r[j] = r[j + 1] - r[j];
        }

        for (int64 j = 1; j <= k + 1; ++j)
        {
            v.emplace_back(l[j - 1], r[j], i);
        }
    }

    std::ranges::sort(v);
    
    int64 ans = 0;
    
    std::vector<int64> last(n, -1);
    std::multiset<int64> set;

    for (int64 i = 0; i < v.size(); ++i)
    {
        if (~last[std::get<2>(v[i])])
        {
            set.extract(last[std::get<2>(v[i])]);
        }

        set.insert(std::get<1>(v[i]));
        last[std::get<2>(v[i])] = std::get<1>(v[i]);

        if (i + 1 == v.size() or std::get<0>(v[i]) != std::get<0>(v[i + 1]))
        {
            if (std::get<0>(v[i]) >= maxl)
            {
                ans = std::max(ans, *set.begin() - std::get<0>(v[i]));
            }
        }
    }

    std::cout << ans;

    return 0;
}