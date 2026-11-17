/**
 * Educational DP Contest
 * 
 * => G - Longest Path ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_g
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/74971911 By huanhuanonly
 * 
 * @b Topological-DP
 * 
 * ----April 15, 2026 [11h:59m:28s]----
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

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> e(n + 1);
    std::vector<int> indeg(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        ++indeg[v];
    }

    std::vector<int> dp(n + 1);

    std::queue<int> que;

    for (int i = 1; i <= n; ++i)
    {
        if (indeg[i] == 0)
        {
            que.push(i);
        }
    }

    while (not que.empty())
    {
        const int u = que.front();
        que.pop();

        for (const auto& i : e[u])
        {
            if (--indeg[i] == 0)
            {
                que.push(i);

                dp[i] = std::max(dp[i], dp[u] + 1);
            }
        }
    }

    std::cout << *std::ranges::max_element(dp);

    return 0;
}