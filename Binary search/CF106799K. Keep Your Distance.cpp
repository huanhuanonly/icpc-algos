/**
 * The 2026 ICPC Asia Chengdu Regional Contest (The 5th Universal Cup. Stage 5: Grand Prix of Chengdu)
 *
 * => K. Keep Your Distance
 *
 * -> https://codeforces.com/gym/106799/problem/K
 *
 * Submissions ~> https://codeforces.com/gym/106799/submission/397407950 By huanhuanonly
 *
 * @b Binary-search
 *
 * ----November 05, 2026 [03h:00m:27s]----
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
        int n;
        std::cin >> n;

        std::vector<int64> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        std::vector<int64> l(n);

        for (int i = 1; i < n; ++i)
        {
            std::cin >> l[i];
        }

        auto check = [&](int64 mid) -> bool
        {
            std::list<std::pair<int64, int64>> list{{v[0] - mid, v[0] + mid}};

            for (int i = 1; i < n; ++i)
            {
                for (auto it = list.begin(); it != list.end(); ++it)
                {
                    list.emplace(it, v[i] - mid, std::min(v[i] + mid, it->second - l[i]));

                    it->first = std::max(v[i] - mid, it->first + l[i]);
                    it->second = v[i] + mid;
                }

                for (auto it = list.begin(); it != list.end(); )
                {
                    if (it->first > it->second)
                    {
                        it = list.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }

                if (list.empty())
                {
                    return false;
                }

                list.sort();

                for (auto pit = list.begin(), it = std::next(pit); it != list.end(); )
                {
                    if (pit->second >= it->first)
                    {
                        pit->second = std::max(pit->second, it->second);
                        it = list.erase(it);
                    }
                    else
                    {
                        ++pit;
                        ++it;
                    }
                }
            }

            return not list.empty();
        };

        int64 lo = -1, hi = 1e9, mid;

        while (hi - lo > 1)
        {
            mid = lo + hi >> 1;

            if (check(mid))
            {
                hi = mid;
            }
            else
            {
                lo = mid;
            }
        }

        std::cout << hi << '\n';
    }

    return 0;
}