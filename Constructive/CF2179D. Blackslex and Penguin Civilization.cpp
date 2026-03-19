/**
 * Codeforces Round 1071 (Div. 3)
 * 
 * => D. Blackslex and Penguin Civilization ( @c 1300 )
 * 
 * -> https://codeforces.com/contest/2179/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/2179/submission/354777785 By huanhuanonly
 * 
 * @b Constructive and @b Bitwise-AND
 * 
 * ----December 23, 2025 [23h:41m:47s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        uint32 n;
        std::cin >> n;

        std::vector<bool> vis(1 << n);

        for (uint32 i = (1 << n) - 1; i > 0; i ^= std::bit_floor(i))
        {
            for (uint32 j = 0; j < vis.size(); ++j)
            {
                if (not vis[j] and (j & i) == i)
                {
                    std::cout << j << ' ';
                    vis[j] = true;
                }
            }
        }

        for (uint32 i = 0; i < vis.size(); ++i)
        {
            if (not vis[i])
            {
                std::cout << i << ' ';
            }
        }

        std::cout.put('\n');
    }

    return 0;
}