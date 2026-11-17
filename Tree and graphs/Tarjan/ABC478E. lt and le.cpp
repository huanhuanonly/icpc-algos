/**
 * AtCoder Beginner Contest 478
 *
 * => E - lt and le ( @c 475 )
 *
 * -> https://atcoder.jp/contests/abc478/tasks/abc478_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc478/submissions/80042982 By huanhuanonly
 *
 * @b Tarjan ( @a strong-connectivity-component )
 * @b Dfs on @a Trees
 *
 * ----October 14, 2026 [21h:21m:59s]----
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

    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<std::pair<int, int>>> e(n + 1);
    bool yes = true;

    for (int i = 0; i < q; ++i)
    {
        int t, u, v;
        std::cin >> t >> u >> v;

        if (u == v)
        {
            yes = yes and not t;
        }
        else
        {
            e[u].emplace_back(v, t);
        }
    }

    std::vector<std::pair<int, int>> dfn(n + 1);

    std::stack<int> stack;
    std::vector<bool> instack(n + 1);

    std::vector<int> scc(n + 1);

    std::vector<bool> vis(n + 1);

    auto dfs = [&, id = 0](auto& self, int u) mutable -> void
    {
        dfn[u].first = dfn[u].second = ++id;
        vis[u] = true;

        stack.push(u);
        instack[u] = true;

        for (const auto& [v, t] : e[u])
        {
            if (not vis[v])
            {
                self(self, v);
                dfn[u].second = std::min(dfn[u].second, dfn[v].second);
            }
            else if (instack[v])
            {
                dfn[u].second = std::min(dfn[u].second, dfn[v].first);
            }
        }

        if (dfn[u].first == dfn[u].second)
        {
            for (; stack.top() != u; scc[stack.top()] = u, instack[stack.top()] = false, stack.pop());

            scc[u] = u;

            instack[u] = false;
            stack.pop();
        }
    };

    for (int u = 1; u <= n; ++u)
    {
        if (not vis[u])
        {
            dfs(dfs, u);
        }
    }

    std::vector<std::vector<std::pair<int, int>>> ne(n + 1);

    for (int u = 1; u <= n; ++u)
    {
        for (const auto& [v, t] : e[u])
        {
            if (scc[u] == scc[v])
            {
                yes = yes and not t;
            }
            else
            {
                ne[scc[u]].emplace_back(scc[v], t);
            }
        }
    }

    if (yes)
    {
        std::vector<int> ans(n + 1, n);

        auto calc = [&](const auto& self, int u) -> void
        {
            if (vis[u])
            {
                return;
            }

            vis[u] = true;

            for (const auto& [v, t] : ne[u])
            {
                self(self, v);
                ans[u] = std::min(ans[u], ans[v] - t);
            }
        };

        vis.assign(vis.size(), false);

        for (int u = 1; u <= n; ++u)
        {
            if (not vis[u])
            {
                calc(calc, u);
            }
        }

        std::cout << "Yes\n";

        for (int u = 1; u <= n; ++u)
        {
            std::cout << ans[scc[u]] << " \n"[u == n];
        }
    }
    else
    {
        std::cout << "No\n";
    }

    return 0;
}