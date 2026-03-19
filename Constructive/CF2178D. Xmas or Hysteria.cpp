/**
 * Good Bye 2025
 * 
 * => D. Xmas or Hysteria ( @c 1700 )
 * 
 * -> https://codeforces.com/contest/2178/problem/D
 * 
 * Submissions ~> https://codeforces.com/contest/2178/submission/355818388 By huanhuanonly
 * 
 * @b Constructive
 * 
 * ----December 30, 2025 [08h:54m:51s]----
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
        int n, m;
        std::cin >> n >> m;

        std::vector<std::pair<int64, int64>> h(n + 1);
        std::vector<std::pair<int64, int64>> v(n + 1);

        for (int64 i = 1; i <= n; ++i)
        {
            std::cin >> v[i].first;
            v[i].second = i;

            h[i].first = h[i].second = v[i].first;
        }

        if (m > n / 2)
        {
            std::cout << -1 << '\n';
            continue;
        }

        std::ranges::sort(v);

        std::vector<std::pair<int, int>> ans;
        ans.reserve(n);

        if (m == 0)
        {
            int64 sum = v[n].first;

            int pos = n - 1;
            
            for (; pos >= 1 and sum > v[pos].first; --pos)
            {
                sum -= v[pos].first;
                ans.emplace_back(v[pos].second, v[n].second);
            }

            for (int i = 1; i < pos; ++i)
            {
                ans.emplace_back(v[i].second, v[i + 1].second);
            }

            ans.emplace_back(v[n].second, v[pos].second);
        }
        else
        {
            for (int i = 1; i <= m - 1; ++i)
            {
                ans.emplace_back(v[n - i].second, v[i].second);
            }
    
            for (int i = m; i <= n - m - 1; ++i)
            {
                ans.emplace_back(v[i].second, v[i + 1].second);
            }
    
            ans.emplace_back(v[n].second, v[n - m].second);
        }

        for (const auto& [x, y] : ans)
        {
            h[x].second -= h[y].first;
            h[y].second -= h[x].first;
        }

        if (std::ranges::count(h, true, [](const auto& pair) -> bool { return pair.second > 0; }) == m)
        {
            std::cout << ans.size() << '\n';
    
            for (const auto& [x, y] : ans)
            {
                std::cout << x << ' ' << y << '\n';
            }
        }
        else
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}