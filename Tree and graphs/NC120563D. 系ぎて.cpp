/**
 * 2026牛客寒假算法基础集训营3
 * 
 * => D-系ぎて ( @c 2300 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120563/D
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82198225 By huanhuanonly
 * 
 * @b Dfs on @a Graphs
 * 
 * ----February 08, 2026 [01h:00m:37s]----
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

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

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
        
        std::vector map(n, std::string(m, '0'));
        
        std::vector<std::pair<int, int>> coords;
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                std::cin >> map[i][j];
                
                if (map[i][j] != '0')
                {
                    coords.emplace_back(i, j);
                }
            }
        }
        
        std::ranges::sort(coords, {}, [&](const auto& p) -> char { return map[p.first][p.second]; });

        constexpr std::pair<int, int> d[]{
            {1, 0}, {0, 1}, {-1, 0}, {0, -1}
        };

        auto check = [&](const auto& p) -> bool
        {
            return p.first >= 0 and p.first < n and p.second >= 0 and p.second < m;
        };

        auto onborder = [&](const auto& p) -> bool
        {
            return p.first == 0 or p.first == n - 1 or p.second == 0 or p.second == m - 1;
        };

        auto blocked = [&](const auto& p) -> bool
        {
            for (const auto& [dx, dy] : d)
            {
                const int nx = p.first + dx, ny = p.second + dy;

                if (check(std::make_pair(nx, ny)))
                {
                    if (map[nx][ny] == '0' or map[nx][ny] == map[p.first][p.second])
                    {
                        return false;
                    }
                }
            }

            return true;
        };

        auto intersected = [&](const auto& p) -> bool
        {
            return
                p.first + 1 < n and p.second + 1 < m and
                ((map[p.first][p.second] == '1' and map[p.first][p.second + 1] == '2' and
                map[p.first + 1][p.second] == '2' and map[p.first + 1][p.second + 1] == '1') or
                (map[p.first][p.second] == '2' and map[p.first][p.second + 1] == '1' and
                map[p.first + 1][p.second] == '1' and map[p.first + 1][p.second + 1] == '2'));

        };

        if (not std::ranges::all_of(coords, onborder))
        {
            if (not std::ranges::any_of(coords, blocked) and not std::ranges::any_of(coords, intersected))
            {
                std::cout << "YES\n";
            }
            else
            {
                std::cout << "NO\n";
            }

            continue;
        }

        std::vector vis(n, std::vector(m, false));

        auto dfs = [&](const auto& self, const std::pair<int, int>& c, const std::pair<int, int>& to) -> bool
        {
            vis[c.first][c.second] = true;
            
            if (c == to)
            {
                if (to == coords[3])
                {
                    return true;
                }
                else
                {
                    vis[coords[2].first][coords[2].second] = false;
                    vis[coords[3].first][coords[3].second] = false;
                    
                    const bool arrived = self(self, coords[2], coords[3]);
                    
                    vis[coords[2].first][coords[2].second] = true;
                    vis[coords[3].first][coords[3].second] = true;
                    
                    vis[c.first][c.second] = false;
                    return arrived;
                }
            }

            for (const auto& [dx, dy] : d)
            {
                const int nx = c.first + dx, ny = c.second + dy;

                if (not check(std::make_pair(nx, ny)))
                {
                    continue;
                }

                if ((nx != 0 and nx != n - 1 and dx == 0) or (ny != 0 and ny != m - 1 and dy == 0))
                {
                    continue;
                }
                
                if (not vis[nx][ny] and onborder(std::make_pair(nx, ny)))
                {
                    if (self(self, {nx, ny}, to))
                    {
                        return true;
                    }
                }
            }

            vis[c.first][c.second] = false;

            return false;
        };

        vis[coords[2].first][coords[2].second] = true;
        vis[coords[3].first][coords[3].second] = true;

        if (dfs(dfs, coords[0], coords[1]))
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}