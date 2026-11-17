/**
 * Codeforces Round 244 (Div. 2)
 *
 * => C. Checkposts ( @c 1700 )
 *
 * -> https://codeforces.com/contest/427/problem/C
 *
 * Submissions ~> https://codeforces.com/contest/427/submission/388699536 By huanhuanonly
 *
 * @b Tarjan's-algorithm ( @a strongly-connected-component )
 *
 * ----August 29, 2026 [00h:52m:14s]----
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

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> w(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> w[i].first;
        w[i].second = 1;
    }

    int m;
    std::cin >> m;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
    }

    std::vector<bool> vis(n + 1);
    std::vector<std::pair<int, int>> dfn(n + 1);

    std::stack<int> stack;
    std::vector<bool> instack(n + 1);

    std::vector<int> scc(n + 1);

    auto dfs = [&, id = 0](auto& self, int u) mutable -> void
    {
        vis[u] = true;
        dfn[u].first = dfn[u].second = ++id;

        instack[u] = true;
        stack.push(u);

        for (const auto& v : e[u])
        {
            if (not vis[v])
            {
                self(self, v);
                dfn[u].second = std::min(dfn[u].second, dfn[v].second);
            }
            else if (instack[v])
            {
                dfn[u].second = std::min(dfn[u].second, dfn[v].second);
            }
        }

        if (dfn[u].first == dfn[u].second)
        {
            for (; stack.top() != u; instack[stack.top()] = false, stack.pop())
            {
                scc[stack.top()] = u;

                if (w[stack.top()].first < w[u].first)
                {
                    w[u] = {w[stack.top()].first, 1};
                }
                else if (w[stack.top()].first == w[u].first)
                {
                    ++w[u].second;
                }
            }

            instack[u] = false;
            stack.pop();

            scc[u] = u;
        }
    };

    for (int u = 1; u <= n; ++u)
    {
        if (not vis[u])
        {
            dfs(dfs, u);
        }
    }

    constexpr uint64 mod = 1e9 + 7;
    uint64 sum = 0, cnt = 1;

    for (int u = 1; u <= n; ++u)
    {
        if (scc[u] == u)
        {
            sum += w[u].first;
            cnt *= w[u].second;
            cnt %= mod;
        }
    }

    std::cout << sum << ' ' << cnt << '\n';

    return 0;
}