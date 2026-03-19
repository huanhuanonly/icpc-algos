/**
 * Codeforces Round 1080 (Div. 3)
 * 
 * => G. Idiot First Search and Queries ( @c 2300 )
 * 
 * -> https://codeforces.com/contest/2195/problem/G
 * 
 * Submissions ~> https://codeforces.com/contest/2195/submission/365688685 By huanhuanonly
 * 
 * @b Trees
 * @b Binary-lifting
 * @b Euler-order
 * 
 * ----March 07, 2026 [15h:28m:36s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, q;
        std::cin >> n >> q;

        std::vector<std::array<int, 2>> e(n + 1);

        constexpr int laycnt = 30;
        constexpr int maxk = 1e9 + 7;

        std::vector<std::array<int, laycnt>> fa(n + 1), cnt(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> e[i][0] >> e[i][1];
            fa[e[i][0]][0] = fa[e[i][1]][0] = i;
        }

        std::vector<int> sizes(n + 1, 1);
        
        std::vector<int> que;
        que.reserve(n * 3);

        std::vector<int> pos(n + 1);
        
        auto dfs = [&](const auto& self, int u) -> void
        {
            pos[u] = que.size();
            que.push_back(u);
            
            if (e[u][0])
            {
                self(self, e[u][0]);
                sizes[u] += sizes[e[u][0]];
                
                que.push_back(u);

                self(self, e[u][1]);
                sizes[u] += sizes[e[u][1]];
                
                que.push_back(u);
            }
        };
        
        dfs(dfs, 1);

        cnt[0][0] = 0;

        for (int i = 1; i <= n; ++i)
        {
            cnt[i][0] = sizes[i] * 2 - 1;
        }

        for (int i = 1; i < laycnt; ++i)
        {
            for (int u = 1; u <= n; ++u)
            {
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
                cnt[u][i] = std::min(maxk + 1, cnt[u][i - 1] + cnt[fa[u][i - 1]][i - 1]);
            }
        }

        while (q--)
        {
            int v, k;
            std::cin >> v >> k;

            for (int i = laycnt - 1; i >= 0; --i)
            {
                if (k >= cnt[v][i])
                {
                    k -= cnt[v][i];
                    v = fa[v][i];
                }
            }

            std::cout << que[pos[v] + k] << ' ';
        }

        std::cout.put('\n');
    }

    return 0;
}