/**
 * => P3387 【模板】缩点 ( @c 普及+/提高 )
 *
 * -> https://www.luogu.com.cn/problem/P3387
 *
 * Submissions ~> https://www.luogu.com.cn/record/160862435 By huanhuanonly
 *
 * @b Tarjan's-algorithm ( @a strongly-connected-component )
 *
 * ----May 31, 2024 [21h:37m:07s]----
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

    std::vector<int> v(n + 1);

    std::vector<int> scc(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        scc[i] = i;
    }

    std::vector<std::pair<int, int>> data(m + 1);
    std::vector<std::vector<int>> e(n + 1);

    for (int i = 1; i <= m; ++i)
    {
        std::cin >> data[i].first >> data[i].second;

        e[data[i].first].push_back(data[i].second);
    }

    std::vector<bool> vis(n + 1);

    std::vector<std::pair<int, int>> dfn(n + 1);
    int time = 0;

    std::stack<int, std::vector<int>> st;

    std::function<int(int)> dfs = [&](int u) -> int
    {
        st.push(u);
        vis[u] = true;
        dfn[u].first = dfn[u].second = ++time;

        for (const auto& i : e[u])
        {
            if (dfn[i].first == 0)
            {
                dfs(i);
                dfn[u].second = std::min(dfn[u].second, dfn[i].second);
            }
            else if (vis[i])
            {
                dfn[u].second = std::min(dfn[u].second, dfn[i].first);
            }
        }

        if (dfn[u].first == dfn[u].second)
        {
            while (st.top() != u)
            {
                vis[st.top()] = false;
                scc[st.top()] = u;

                v[u] += v[st.top()];
                st.pop();
            }
            vis[st.top()] = false;
            st.pop();
        }

        return 0;
    };

    for (int i = 1; i <= n; ++i)
        if (dfn[i].first == 0)
            dfs(i);

    for (int i = 1; i <= n; ++i)
        e[i].clear();

    for (int i = 1; i <= m; ++i)
    {
        if (scc[data[i].first] != scc[data[i].second])
        {
            e[scc[data[i].first]].push_back(scc[data[i].second]);
        }
    }

    int ans = 0;

    std::map<int, int> mp;

    dfs = [&](int u) -> int
    {
        if (mp.find(u) != mp.end())
            return mp[u];

        int mx = 0;
        for (const auto& i : e[u])
        {
            mx = std::max(mx, dfs(i));
        }

        ans = std::max(ans, mx + v[u]);
        return mp[u] = mx + v[u];
    };

    for (int i = 1; i <= n; ++i)
        dfs(i);

    std::cout << ans;

    return 0;
}