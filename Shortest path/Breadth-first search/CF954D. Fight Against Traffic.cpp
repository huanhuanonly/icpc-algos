/**
 * Educational Codeforces Round 40 (Rated for Div. 2)
 *
 * => D. Fight Against Traffic ( @c 1600 )
 *
 * -> https://codeforces.com/contest/954/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/954/submission/339714201 By huanhuanonly
 *
 * @b Breadth-first-search
 *
 * ----September 21, 2025 [22h:20m:50s]----
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

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    std::vector<std::set<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].insert(v);
        e[v].insert(u);
    }

    std::vector<int> sdis(n + 1);
    std::vector<int> tdis(n + 1);

    auto bfs = [&](int start, std::vector<int>& dis) -> void
    {
        std::vector<bool> vis(n + 1);

        std::queue<std::pair<int, int>> que;
        que.push({start, 0});

        vis[start] = true;

        while (not que.empty())
        {
            auto [u, d] = que.front();
            que.pop();

            for (int i : e[u])
            {
                if (not vis[i])
                {
                    vis[i] = true;
                    dis[i] = d + 1;
                    que.push({i, d + 1});
                }
            }
        }
    };

    bfs(s, sdis);
    bfs(t, tdis);

    int cnt = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (sdis[i] + 1 + tdis[j] >= sdis[t] and sdis[j] + 1 + tdis[i] >= sdis[t] and not e[i].contains(j))
            {
                ++cnt;
            }
        }
    }

    std::cout << cnt;

    return 0;
}