/**
 * Codeforces Round 1075 (Div. 2)
 * 
 * => C1. XOR Convenience (Easy Version) ( @c 1300 )
 * 
 * -> https://codeforces.com/contest/2189/problem/C1
 * 
 * Submissions ~> https://codeforces.com/contest/2189/submission/359402730 By huanhuanonly
 * 
 * @b Constructive and @b Bitwise-XOR
 * 
 * ----January 23, 2026 [23h:26m:29s]----
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
        int n;
        std::cin >> n;

        std::vector<int> v(n + 1);
        std::vector<bool> vis(n + 1);

        vis[v[n] = 1] = true;

        for (int i = 2; i <= n - 1; ++i)
        {
            vis[v[i] = v[n] ^ i] = true;
        }

        vis[0] = true;
        v[1] = std::ranges::find(vis, false) - vis.begin();

        for (int i = 1; i <= n; ++i)
        {
            std::cout << v[i] << " \n"[i == n];
        }
    }

    return 0;
}