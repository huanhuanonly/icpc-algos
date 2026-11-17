/**
 * Codeforces Round 333 (Div. 1)
 *
 * => A. The Two Routes ( @c 1600 )
 *
 * -> https://codeforces.com/contest/601/problem/A
 *
 * Submissions ~> https://codeforces.com/contest/601/submission/241283801 By huanhuanonly
 *
 * @b Floyd–Warshall-algorithm
 *
 * ----January 12, 2024 [21h:16m:35s]----
*/

#include <bits/stdc++.h>

using llong = long long;
using ullong = unsigned long long;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> mp(n + 1, std::vector<int>(n + 1, 0x3f3f3f3f));
    std::vector<std::vector<int>> mp2(n + 1, std::vector<int>(n + 1, 0x3f3f3f3f));

    int u, v;
    for (int i = 0; i < m; ++i)
    {
        std::cin >> u >> v;
        mp[u][v] = mp[v][u] = 1;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (mp[i][j] ^ 1)
                mp2[i][j] = mp2[j][i] = 1;

    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                mp[i][j] = std::min(mp[i][j], mp[i][k] + mp[k][j]);
                mp2[i][j] = std::min(mp2[i][j], mp2[i][k] + mp2[k][j]);
            }
        }
    }

    if (int mx = std::max(mp[1][n], mp2[1][n]); mx != 0x3f3f3f3f)
        std::cout << mx << '\n';
    else
        std::cout << -1 << '\n';

    return 0;
}