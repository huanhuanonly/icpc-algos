/**
 * Codeforces Round 903 (Div. 3)
 *
 * => F. Minimum Maximum Distance ( @c 1700 )
 *
 * -> https://codeforces.com/contest/1881/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/1881/submission/251248734 By huanhuanonly
 *
 * @b Breadth-first-search
 *
 * ----March 14, 2024 [21h:44m:47s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> a(k);
        for (int i = 0; i < k; ++i)
            std::cin >> a[i];

        std::vector<std::vector<int>> e(n + 1);

        for (int i = 1; i < n; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            e[u].push_back(v);
            e[v].push_back(u);
        }

        auto bfs = [&](int start) -> std::pair<int, int>
        {
            // dis, point
            std::pair<int, int> ans;

            struct node
            {
                int to, last, dis;
            };

            std::queue<node> que;
            que.push({start, 0});

            while (not que.empty())
            {
                node ct = que.front();
                que.pop();

                if (std::binary_search(a.begin(), a.end(), ct.to))
                {
                    ans = std::max(ans, {ct.dis, ct.to});
                }

                for (const int& i : e[ct.to])
                {
                    if (i == ct.last)
                        continue;

                    que.push({i, ct.to, ct.dis + 1});
                }
            }

            return ans;
        };

        int point = bfs(a.front()).second;
        int dis   = bfs(point).first;

        std::cout << dis / 2 + dis % 2 << '\n';
    }

    return 0;
}