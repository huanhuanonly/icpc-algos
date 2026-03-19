/**
 * Codeforces Round 1075 (Div. 2)
 * 
 * => C2. XOR-convenience (Hard Version) ( @c 1800 )
 * 
 * -> https://codeforces.com/contest/2189/problem/C2
 * 
 * Submissions ~> https://codeforces.com/contest/2189/submission/360014031 By huanhuanonly
 * 
 * @b Constructive and @b Bitwise-XOR
 * 
 * ----January 26, 2026 [23h:33m:31s]----
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

        std::vector<uint32> v(n + 1);

        for (uint32 i = 2; i < n; ++i)
        {
            v[i] = i ^ 1;
        }

        v[1] = n & ~1;
        v[n] = 1;

        if (std::has_single_bit(n))
        {
            std::cout << -1 << '\n';
        }
        else
        {
            if (n & 1 ^ 1)
            {
                std::swap(v[1], v[v[1] & -v[1]]);
            }

            for (uint32 i = 1; i <= n; ++i)
            {
                std::cout << v[i] << " \n"[i == n];
            }
        }
    }

    return 0;
}