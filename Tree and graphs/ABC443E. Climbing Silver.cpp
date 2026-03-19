/**
 * Denso Create Programming Contest 2026（AtCoder Beginner Contest 443）
 * 
 * => E - Climbing Silver ( @c 450 )
 * 
 * -> https://atcoder.jp/contests/abc443/tasks/abc443_e
 * 
 * Submissions ~> https://atcoder.jp/contests/abc443/submissions/72912632 By huanhuanonly
 * 
 * @b Bfs
 * 
 * ----January 31, 2026 [22h:08m:04s]----
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
        int n, c;
        std::cin >> n >> c;

        --c;

        std::vector<std::string> mp(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> mp[i];
        }

        std::vector<int> waiting(n, n - 1);

        auto destroy = [&](int j) -> void
        {
            mp[waiting[j]][j] = '.';
            
            for (; waiting[j] >= 0 and mp[waiting[j]][j] == '.'; --waiting[j]);
        };

        for (int j = 0; j < n; ++j)
        {
            if (mp[n - 1][j] == '.')
            {
                destroy(j);
            }
        }

        std::vector vis(n, std::string(n, '0'));

        std::queue<std::pair<int, int>> que;
        que.emplace(n - 1, c);

        while (not que.empty())
        {
            const auto [cx, cy] = que.front();
            que.pop();

            if (cx == 0)
            {
                continue;
            }

            for (int i = -1; i <= 1; ++i)
            {
                const int nx = cx - 1, ny = cy + i;
                if (0 <= ny and ny < n and vis[nx][ny] == '0')
                {
                    if (mp[nx][ny] == '#')
                    {
                        if (waiting[ny] == nx)
                        {
                            destroy(ny);
                        }
                        else
                        {
                            continue;
                        }
                    }

                    vis[nx][ny] = '1';
                    que.emplace(nx, ny);
                }
            }
        }

        std::cout << vis[0] << '\n';
    }

    return 0;
}