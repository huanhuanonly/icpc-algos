/**
 * => P3388 【模板】割点（割顶） ( @c 普及+/提高 )
 *
 * -> https://www.luogu.com.cn/problem/P3388
 *
 * Submissions ~> https://www.luogu.com.cn/record/160792460 By huanhuanonly
 *
 * @b Tarjan's-algorithm ( @a articulation-point )
 *
 * ----May 31, 2024 [11h:25m:54s]----
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

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<std::pair<int, int>> dfn(n + 1);

    int time = 0;
    std::set<int> ans;

    std::function<void(int, int)> dfs = [&](int u, int fa) -> void
    {
        dfn[u].first = dfn[u].second = ++time;

        int cnt = 0;

        for (const auto& i : e[u])
        {
            if (dfn[i].first == 0)
            {
                dfs(i, fa);
                ++cnt;
                dfn[u].second = std::min(dfn[u].second, dfn[i].second);

                if (dfn[i].second >= dfn[u].first and u != fa)
                    ans.insert(u);
            }
            else
            {
                dfn[u].second = std::min(dfn[u].second, dfn[i].first);
            }
        }

        if (u == fa and cnt >= 2)
            ans.insert(u);
    };

    for (int i = 1; i <= n; ++i)
        if (dfn[i].first == 0)
            dfs(i, i);

    std::cout << ans.size() << '\n';

    for (const auto& i : ans)
        std::cout << i << ' ';

    return 0;
}