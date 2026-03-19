/**
 * Codeforces Round 1075 (Div. 2)
 * 
 * => D1. Little String (Easy Version) ( @c 1900 )
 * 
 * -> https://codeforces.com/contest/2189/problem/D1
 * 
 * Submissions ~> https://codeforces.com/contest/2189/submission/359431031 By huanhuanonly
 * 
 * @b Combinatorics
 * 
 * ----January 24, 2026 [00h:09m:05s]----
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
        uint64 n, c;
        std::cin >> n >> c;

        std::string s;
        std::cin >> s;

        constexpr uint64 mod = 1e9 + 7;

        if (s.front() != '1' or s.back() != '1')
        {
            std::cout << -1 << '\n';
        }
        else
        {
            uint64 ans = 1, tmp = 1;

            for (uint64 i = 1; i < n; ++i)
            {
                if (s[i] == '1')
                {
                    (ans *= 2) %= mod;
                    (tmp *= 2) %= c;
                }
                else
                {
                    (ans *= i) %= mod;
                    (tmp *= i) %= c;
                }
            }

            if (tmp)
            {
                std::cout << ans << '\n';
            }
            else
            {
                std::cout << -1 << '\n';
            }
        }
    }

    return 0;
}