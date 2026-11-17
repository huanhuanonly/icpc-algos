/**
 * 2025-2026 国际大学生程序设计竞赛贵州省赛
 *
 * => J. 夜郎弈棋
 *
 * -> https://codeforces.com/gym/615540/problem/J
 *
 * Submissions ~> https://codeforces.com/gym/615540/submission/385435058 By huanhuanonly
 *
 * @b Dfs-enumeration
 *
 * ----August 04, 2026 [00h:18m:58s]----
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

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector map(n, std::vector(m, 0));

    for (int i = 0; i < q; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        map[x][y] = -1;
    }

    auto place = [&](int x, int y, int add) -> void
    {
        for (int i = x; i < n; ++i)
        {
            if (map[i][y] == -1)
            {
                break;
            }

            map[i][y] += add;
        }

        for (int j = y; j < m; ++j)
        {
            if (map[x][j] == -1)
            {
                break;
            }

            map[x][j] += add;
        }
    };

    int ans = 0;

    auto dfs = [&](const auto& self, int pos, int cnt) -> void
    {
        if (pos == n * m)
        {
            ans = std::max(ans, cnt);
            return;
        }

        const auto [x, y] = std::div(pos, m);

        if (not map[x][y])
        {
            place(x, y, +1);
            self(self, pos + 1, cnt + 1);
            place(x, y, -1);
        }

        self(self, pos + 1, cnt);
    };

    dfs(dfs, 0, 0);

    std::cout << ans << '\n';

    return 0;
}