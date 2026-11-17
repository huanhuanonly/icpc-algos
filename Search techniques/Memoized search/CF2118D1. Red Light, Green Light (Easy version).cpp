/**
 * Codeforces Round 1030 (Div. 2)
 * 
 * => D1. Red Light, Green Light (Easy version) ( @c 1700 )
 * 
 * -> https://codeforces.com/contest/2118/problem/D1
 * 
 * Submissions ~> https://codeforces.com/contest/2118/submission/324190265 By huanhuanonly
 * 
 * @b Memoized-search
 * 
 * ----June 13, 2025 [10h:58m:50s]----
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
        int n, k;
        std::cin >> n >> k;

        std::vector<uint64> p(n), d(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> p[i];
        }

        for (int i = 0; i < n; ++i)
        {
            std::cin >> d[i];
        }

        std::set<std::pair<int, bool>> vis;

        auto dfs = [&](const auto& self, int pos, bool dir, uint64 time) -> bool
        {
            bool is_red = (time == d[pos]);

            if (is_red)
            {
                dir = not dir;
            }

            if (pos < 0 or pos >= n)
            {
                return true;
            }
            else if (dir and pos == n - 1)
            {
                return true;
            }
            else if (not dir and pos == 0)
            {
                return true;
            }

            if (is_red)
            {
                if (vis.find({pos, dir}) != vis.end())
                {
                    return false;
                }
                else
                {
                    vis.insert({pos, dir});
                }
            }

            if (dir)
            {
                return self(self, pos + 1, dir, (time + (p[pos + 1] - p[pos])) % k);
            }
            else
            {
                return self(self, pos - 1, dir, (time + (p[pos] - p[pos - 1])) % k);
            }
        };

        int q;
        std::cin >> q;

        for (int i = 0; i < q; ++i)
        {
            uint64 a;
            std::cin >> a;

            if (a < p.front())
            {
                std::cout << "YES\n";
                continue;
            }

            auto it = std::ranges::lower_bound(p, a);

            if (it == p.end())
            {
                std::cout << "YES\n";
                continue;
            }

            if (dfs(dfs, it - p.begin(), true, (*it - a) % k))
            {
                std::cout << "YES\n";
            }
            else
            {
                std::cout << "NO\n";
            }

            vis.clear();
        }
    }

    return 0;
}