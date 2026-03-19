/**
 * 2025-2026 ICPC, NERC, Northern Eurasia Finals (Unrated, Online Mirror, ICPC Rules, Teams Preferred)
 * 
 * => F. Fragmented Nim ( @c 1600 )
 * 
 * -> https://codeforces.com/contest/2181/problem/F
 * 
 * Submissions ~> https://codeforces.com/contest/2181/submission/356501394 By huanhuanonly
 * 
 * @b Game-theory
 * 
 * ----January 05, 2026 [21h:18m:26s]----
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

        std::vector<int> v(n);

        int cnt = 0;

        for (auto& i : v)
        {
            std::cin >> i;
            cnt += i == 1;
        }

        if (cnt & 1 ^ cnt != n)
        {
            std::cout << "Alice\n";
        }
        else
        {
            std::cout << "Bob\n";
        }
    }

    return 0;
}