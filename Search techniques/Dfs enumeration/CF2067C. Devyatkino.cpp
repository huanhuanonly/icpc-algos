/**
 * Codeforces Round 1004 (Div. 2)
 * 
 * => C. Devyatkino ( @c 1500 )
 * 
 * -> https://codeforces.com/contest/2067/problem/C
 * 
 * Submissions ~> https://codeforces.com/contest/2067/submission/347353886 By huanhuanonly
 * 
 * @b Dfs-enumeration
 * 
 * ----November 04, 2025 [14h:13m:30s]----
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

bool contains(uint64 x, int d)
{
    for (; x; x /= 10)
    {
        if (x % 10 == d)
        {
            return true;
        }
    }

    return false;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    std::vector<uint64> add{9};

    for (int i = 1; i < 9; ++i)
    {
        add.push_back(add.back() * 10 + 9);
    }

    std::ranges::reverse(add);

    int _;
    std::cin >> _;

    while (_--)
    {
        uint64 n;
        std::cin >> n;

        for (int k = 0; k <= 9; ++k)
        {
            auto dfs = [&](const auto& self, uint64 x, int d, int i = 0) -> bool
            {
                if (d == k)
                {
                    return contains(x, 7);
                }
     
                for (; i < add.size(); ++i)
                {
                    if (self(self, x + add[i], d + 1, i))
                    {
                        return true;
                    }
                }
     
                return false;
            };

            if (dfs(dfs, n, 0))
            {
                std::cout << k << '\n';
                break;
            }
        }
    }

    return 0;
}