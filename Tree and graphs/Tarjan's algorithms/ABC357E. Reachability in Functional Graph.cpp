/**
 * SuntoryProgrammingContest2024（AtCoder Beginner Contest 357）
 *
 * => E - Reachability in Functional Graph ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc357/tasks/abc357_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc357/submissions/54456805 By huanhuanonly
 *
 * @b Tarjan's-algorithm ( @a strongly-connected-component )
 *
 * ----June 11, 2024 [19h:23m:10s]----
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

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> e(n + 1);

    std::vector<int> data(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> data[i];
        e[i].push_back(data[i]);
    }

    std::vector<std::pair<int, int>> dfn(n + 1);

    std::stack<int> st;
    std::vector<bool> vis(n + 1);
    std::vector<int> scc(n + 1);

    std::vector<int> in(n + 1);
    std::vector<int> size(n + 1, 1);

    int timing;

    std::function<int(int)> dfs = [&](int u) -> int
    {
        dfn[u].first = dfn[u].second = ++timing;
        st.push(u);
        vis[u] = true;

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
                scc[st.top()] = u;
                vis[st.top()] = false;
                size[u] += size[st.top()];
                st.pop();
            }

            vis[u] = false;
            scc[u] = u;
            st.pop();
        }

        return 0;
    };

    for (int i = 1; i <= n; ++i)
        if (scc[i] == 0)
            timing = 0,
            dfs(i);

    for (auto& i : e)
        i.clear();

    for (int i = 1; i <= n; ++i)
        if (scc[i] != scc[data[i]])
            ++in[scc[data[i]]],
            e[scc[i]].push_back(scc[data[i]]);

    ullong ans = 0;

    std::map<int, int> mp;

    dfs = [&](int u) -> int
    {
        if (mp.contains(u))
            return mp[u];

        int sum = 0;

        for (const auto& i : e[u])
        {
            sum += dfs(i);
        }

        ans += ullong(size[u]) * sum + ullong(size[u]) * size[u];

        return mp[u] = sum + size[u];
    };

    for (int i = 1; i <= n; ++i)
        if (in[i] == 0 and scc[i] == i)
            dfs(i);

    std::cout << ans;

    return 0;
}