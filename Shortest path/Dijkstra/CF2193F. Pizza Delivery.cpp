/**
 * Codeforces Round 1076 (Div. 3)
 * 
 * => F. Pizza Delivery ( @c 1600 )
 * 
 * -> https://codeforces.com/contest/2193/problem/F
 * 
 * Submissions ~> https://codeforces.com/contest/2193/submission/359893879 By huanhuanonly
 * 
 * @b Dijkstra
 * 
 * ----January 26, 2026 [01h:44m:45s]----
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
        int n, sx, sy, tx, ty;
        std::cin >> n >> sx >> sy >> tx >> ty;

        std::vector<int> xs(n), ys(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> xs[i];
        }

        for (int i = 0; i < n; ++i)
        {
            std::cin >> ys[i];
        }

        std::map<int, std::vector<int>> mp;

        for (int i = 0; i < n; ++i)
        {
            mp[xs[i]].push_back(ys[i]);
        }

        int64 ans = tx - sx;

        for (auto it = mp.begin(); it != mp.end(); ++it)
        {
            std::ranges::sort(it->second);
        }

        struct item
        {
            int x, y;
            int64 d;

            bool operator<(const item& other) const
            {
                return d > other.d;
            }
        };

        std::map<std::pair<int, int>, int64> dis;
        std::set<std::pair<int, int>> vis;

        std::priority_queue<item> que;

        if (mp[sx].empty())
        {
            dis[{sx, sy}] = 0;
            que.emplace(sx, sy, 0);
        }
        else
        {
            int64 ndis = std::abs(sy - mp[sx].back()) + std::abs(mp[sx].back() - mp[sx].front());
            dis[{sx, mp[sx].front()}] = ndis;
            que.emplace(sx, mp[sx].front(), ndis);

            ndis = std::abs(sy - mp[sx].front()) + std::abs(mp[sx].front() - mp[sx].back());
            dis[{sx, mp[sx].back()}] = ndis;
            que.emplace(sx, mp[sx].back(), ndis);
        }

        while (not que.empty())
        {
            auto cur = que.top();
            que.pop();

            if (vis.contains({cur.x, cur.y}))
            {
                continue;
            }

            vis.emplace(cur.x, cur.y);

            auto it = mp.upper_bound(cur.x);

            if (it == mp.end())
            {
                continue;
            }

            int a = it->second.front(), b = it->second.back();

            for (int i = 0; i < 2; ++i)
            {
                const int64 ndis = dis[{cur.x, cur.y}] + std::abs(cur.y - b) + std::abs(b - a);

                if (auto fit = dis.find({it->first, a}); fit == dis.end() or fit->second > ndis)
                {
                    dis[{it->first, a}] = ndis;
                    que.emplace(it->first, a, ndis);
                }

                std::swap(a, b);
            }
        }

        auto min = std::numeric_limits<int64>::max();

        for (auto it = dis.rbegin(); it != dis.rend(); ++it)
        {
            if (it->first.first == dis.rbegin()->first.first)
            {
                min = std::min(min, std::abs(it->first.second - ty) + it->second);
            }
            else
            {
                break;
            }
        }

        ans += min;

        std::cout << ans << '\n';
    }

    return 0;
}