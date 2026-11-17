/**
 * Educational Codeforces Round 129 (Rated for Div. 2)
 * 
 * => D. Required Length ( @c 1700 )
 * 
 * -> https://codeforces.com/contest/1681/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/1681/submission/343060166 By huanhuanonly
 * 
 * @b Memoized-search
 * 
 * ----October 11, 2025 [11h:24m:01s]----
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

    uint64 n, x;
    std::cin >> n >> x;

    std::map<uint64, int> mp;

    static auto length_of = [](uint64 n) -> uint64
    {
        return static_cast<uint64>(std::ceil(std::log10(n)));
    };

    auto dfs = [&](const auto& self, uint64 value) -> int
    {
        if (const auto len = length_of(value); len > n)
        {
            return -1;
        }
        else if (len == n)
        {
            return 0;
        }
        else if (auto it = mp.find(value); it != mp.end())
        {
            return it->second;
        }

        std::array<bool, 10> vis{};

        for (uint64 t = value; t; t /= 10)
        {
            vis[t % 10] = true;
        }

        constexpr int inf = std::numeric_limits<int>::max();
        int min = inf;

        for (uint64 i = 2; i < vis.size(); ++i)
        {
            if (vis[i])
            {
                if (const int res = self(self, value * i); ~res)
                {
                    min = std::min(min, res + 1);
                }
            }
        }

        if (min == inf)
        {
            return mp[value] = -1;
        }
        else
        {
            return mp[value] = min;
        }
    };

    std::cout << dfs(dfs, x);

    return 0;
}