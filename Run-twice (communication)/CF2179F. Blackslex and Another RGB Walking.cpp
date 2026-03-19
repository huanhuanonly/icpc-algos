/**
 * Codeforces Round 1071 (Div. 3)
 * 
 * => F. Blackslex and Another RGB Walking ( @c 2000 )
 * 
 * -> https://codeforces.com/contest/2179/problem/F
 * 
 * Submissions ~> https://codeforces.com/contest/2179/submission/354882938 By huanhuanonly
 * 
 * @b Run-twice ( @a communication )
 * 
 * ----December 24, 2025 [11h:50m:48s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    std::string runid;
    std::cin >> runid;

    int _;
    std::cin >> _;

    if (runid[0] == 'f')
    {
        while (_--)
        {
            int n, m;
            std::cin >> n >> m;

            std::vector<std::vector<int>> e(n + 1);

            for (int i = 0; i < m; ++i)
            {
                int u, v;
                std::cin >> u >> v;

                e[u].push_back(v);
                e[v].push_back(u);
            }

            std::string s(n + 1, '-');
            std::vector<bool> vis(n + 1);

            auto bfs = [&]() -> void
            {
                std::queue<std::pair<int, int>> que;
                que.emplace(1, 0);

                while (not que.empty())
                {
                    const auto [u, c] = que.front();
                    que.pop();

                    if (vis[u])
                    {
                        continue;
                    }
    
                    vis[u] = true;
    
                    if (c == 0)
                    {
                        s[u] = 'r';
                    }
                    else if (c == 1)
                    {
                        s[u] = 'g';
                    }
                    else
                    {
                        s[u] = 'b';
                    }
    
                    for (const int& i : e[u])
                    {
                        que.emplace(i, (c + 1) % 3);
                    }
                }
            };

            bfs();

            s.erase(s.begin());
            std::cout << s << '\n';
        }
    }
    else
    {
        while (_--)
        {
            int q;
            std::cin >> q;

            while (q--)
            {
                int d;
                std::cin >> d;

                std::string s;
                std::cin >> s;

                std::vector<int> vis(4);

                for (int i = 0; i < d; ++i)
                {
                    if (s[i] == 'r')
                    {
                        vis[1] = i + 1;
                    }
                    else if (s[i] == 'g')
                    {
                        vis[2] = i + 1;
                    }
                    else
                    {
                        vis[3] = i + 1;
                    }
                }

                if (vis[1] and vis[3])
                {
                    std::cout << vis[1] << '\n';
                }
                else if (vis[1] and vis[2])
                {
                    std::cout << vis[2] << '\n';
                }
                else if (vis[2] and vis[3])
                {
                    std::cout << vis[3] << '\n';
                }
                else
                {
                    std::cout << 1 << '\n';
                }
            }
        }
    }

    return 0;
}