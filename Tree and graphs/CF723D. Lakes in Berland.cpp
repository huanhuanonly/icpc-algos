/**
 * Codeforces Round 375 (Div. 2)
 *
 * => D. Lakes in Berland ( @c 1600 )
 *
 * -> https://codeforces.com/contest/723/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/723/submission/387702338 By huanhuanonly
 *
 * @b Dfs on @a Graphs
 *
 * ----August 19, 2026 [23h:58m:21s]----
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

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::string> map(n);

    for (std::string& i : map)
    {
        std::cin >> i;
    }

    std::vector groupof(n, std::vector<int>(m));

    auto dfs = [&](const auto& self, int x, int y, int id) -> int
    {
        if (map[x][y] == '*' or groupof[x][y])
        {
            return 0;
        }

        groupof[x][y] = id;

        int cnt = 1;

        for (const auto& [dx, dy] : {std::pair{0, 1}, {1, 0}, {0, -1}, {-1, 0}})
        {
            const int nx = x + dx, ny = y + dy;

            if (nx >= 0 and nx < n and ny >= 0 and ny < m)
            {
                cnt += self(self, nx, ny, id);
            }
        }

        return cnt;
    };

    int id = 0;

    for (int i = 0; i < n; ++i)
    {
        dfs(dfs, i, 0, ++id);
        dfs(dfs, i, m - 1, ++id);
    }

    for (int j = 0; j < m; ++j)
    {
        dfs(dfs, 0, j, ++id);
        dfs(dfs, n - 1, j, ++id);
    }

    std::vector<std::pair<int, int>> que;

    for (int i = 1; i < n - 1; ++i)
    {
        for (int j = 1; j < m - 1; ++j)
        {
            if (map[i][j] == '.' and not groupof[i][j])
            {
                que.emplace_back(dfs(dfs, i, j, ++id), id);
            }
        }
    }

    std::ranges::sort(que);

    k = que.size() - k;
    std::cout << *std::ranges::fold_left_first(que | std::views::take(k) | std::views::keys, std::plus{}) << '\n';

    std::set<int> set;

    for (int i = 0; i < k; ++i)
    {
        set.insert(que[i].second);
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (set.contains(groupof[i][j]))
            {
                std::cout.put('*');
            }
            else
            {
                std::cout.put(map[i][j]);
            }
        }

        std::cout.put('\n');
    }

    return 0;
}