/**
 * => P2756 飞行员配对方案问题 ( @c 普及+/提高 )
 *
 * -> https://www.luogu.com.cn/problem/P2756
 *
 * Submissions ~> https://www.luogu.com.cn/record/158948008 By huanhuanonly
 *
 * @b Bipartite-graph
 * @b Hungarian-algorithm
 *
 * ----May 014, 2024 [09h:09m:16s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int m, n;
    std::cin >> m >> n;

    std::vector<std::vector<int>> e(n + 1);

    int u = 0, v = 0;
    while (true)
    {
        std::cin >> u >> v;

        if (u == -1 and v == -1)
            break;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<int> log(n + 1);
    std::vector<bool> vis(n + 1);

    std::function<bool(int)> dfs = [&](int u) -> bool
    {
        for (int i : e[u])
        {
            if (vis[i])
                continue;

            vis[i] = true;

            if (log[i] == 0 or dfs(log[i]))
            {
                log[i] = u;
                return true;
            }
        }

        return false;
    };

    int ans = 0;

    for (int i = 1; i <= m; ++i)
    {
        vis[i] = true;
        ans += dfs(i);
        std::fill(vis.begin(), vis.end(), false);
    }

    std::cout << ans << '\n';

    for (int i = 1; i <= n; ++i)
    {
        if (log[i])
        {
            std::cout << log[i] << ' ' << i << '\n';
        }
    }

    return 0;
}