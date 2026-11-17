/**
 * 2024 Jiangsu Collegiate Programming Contest
 *
 * => I. Integer Reaction
 *
 * -> https://codeforces.com/gym/105161/problem/I
 *
 * Submissions ~> https://codeforces.com/gym/105161/submission/388994186 By huanhuanonly
 *
 * @b Binary-search
 *
 * ----August 31, 2026 [20h:04m:12s]----
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

    std::vector<int64> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    std::vector<int> c(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> c[i];
    }

    auto check = [&](int64 mid) -> bool
    {
        std::multiset<int64> set;
        int last = c[0];

        for (int i = 0; i < n; ++i)
        {
            if (set.empty() or c[i] == last)
            {
                set.insert(v[i]);
                last = c[i];
            }
            else
            {
                if (const auto it = set.lower_bound(mid - v[i]); it == set.end())
                {
                    return false;
                }
                else
                {
                    set.erase(it);
                }
            }
        }

        return true;
    };

    int64 l = 0, r = 1e9, mid;

    while (r - l > 1)
    {
        mid = l + r >> 1;

        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }

    std::cout << l << '\n';

    return 0;
}