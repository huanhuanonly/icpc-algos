/**
 * The 13th Shandong ICPC Provincial Collegiate Programming Contest
 * 
 * => L. Puzzle: Sashigane
 * 
 * -> https://codeforces.com/gym/104417/problem/L
 * 
 * Submissions ~> https://codeforces.com/gym/104417/submission/360349870 By huanhuanonly
 * 
 * @b Constructive
 * 
 * ----January 28, 2026 [23h:58m:23s]----
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

    int n, x, y;
    std::cin >> n >> x >> y;

    std::vector<std::tuple<int, int, int, int>> set;

    int m = 1;

    for (; x > 1 or y > 1; ++m)
    {
        if (x - 1 >= 1 and y - 1 >= 1)
        {
            --x, --y;
            set.emplace_back(x, y, m, m);
        }
        else if (x - 1 >= 1)
        {
            --x;
            set.emplace_back(x, y + m, m, -m);
        }
        else
        {
            --y;
            set.emplace_back(x + m, y, -m, m);
        }
    }

    for (; m < n; ++m)
    {
        set.emplace_back(x + m, y + m, -m, -m);
    }

    std::cout << "Yes\n";
    std::cout << set.size() << '\n';

    for (const auto& [r, c, h, w] : set)
    {
        std::cout << r << ' ' << c << ' ' << h << ' ' << w << '\n';
    }

    return 0;
}