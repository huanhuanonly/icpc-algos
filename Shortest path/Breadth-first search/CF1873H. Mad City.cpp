/**
 * Codeforces Round 898 (Div. 4)
 *
 * => H. Mad City ( @c 1700 )
 *
 * -> https://codeforces.com/contest/1873/problem/H
 *
 * Submissions ~> https://codeforces.com/contest/1873/submission/251176209 By huanhuanonly
 *
 * @b Breadth-first-search (shortest path)
 * @b Depth-first-search (find circles)
 *
 * ----March 14, 2024 [11h:04m:14s]----
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
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, a, b;
        std::cin >> n >> a >> b;

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 0; i < n; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        std::vector<int> dis_marcel(n + 1), dis_valeriu(n + 1);

        // Obtain the distance from Marcel to any point
        auto bfs_marcel = [&, vis = std::vector<bool>(n + 1)]() mutable -> void
        {
            std::queue<int> que;
            que.push(a);
            vis[a] = true;

            while (not que.empty())
            {
                int ct = que.front();
                que.pop();

                for (const int& i : e[ct])
                {
                    if (vis[i])
                        continue;

                    vis[i] = true;

                    dis_marcel[i] = dis_marcel[ct] + 1;
                    que.push(i);
                }
            }

            return;
        };

        // Find circles in the graphs
        // True if Valeriu can reach the any circle first
        std::function<bool(int, int, int)> dfs_valeriu = [&, vis = std::vector<bool>(n + 1)](int p, int last, int dis) mutable -> bool
        {
            for (const auto& i : e[p])
            {
                if (i == last)
                    continue;

                if (vis[i] or i == b)
                {
                    if (dis_valeriu[i] < dis_marcel[i])
                        return true;

                    continue;
                }

                vis[i] = true;

                dis_valeriu[i] = dis + 1;

                if (dfs_valeriu(i, p, dis + 1))
                    return true;

                vis[i] = false;
            }

            return false;
        };

        std::cout << ((bfs_marcel(), dfs_valeriu(b, b, 0)) ? "YES\n" : "NO\n");
    }

    return 0;
}