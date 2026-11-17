/**
 * Codeforces Round 179 (Div. 1)
 *
 * => B. Greg and Graph ( @c 1700 )
 *
 * -> https://codeforces.com/contest/295/problem/B
 *
 * Submissions ~> https://codeforces.com/contest/295/submission/249600754 By huanhuanonly
 *
 * @b Floyd ( @a dynamic-insertion )
 *
 * ----March 04, 2024 [21h:46m:15s]----
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

    int n;
    std::cin >> n;

    constexpr const ullong inf = std::numeric_limits<decltype(inf)>::max() / 2 - 1;

    std::vector<std::vector<ullong>> mp(n + 1, std::vector<ullong>(n + 1, inf));
    std::vector<std::vector<ullong>> dis(n + 1, std::vector<ullong>(n + 1, inf));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> mp[i][j];

    std::vector<int> points(n);

    for (int i = 0; i < n; ++i)
        std::cin >> points[i];

    std::reverse(points.begin(), points.end());

    std::vector<ullong> ans(n);

    ullong sum = 0;

    for (int k = 0; k < points.size(); ++k)
    {
        // Insert the point points[k]
        for (int i = 0; i <= k; ++i)
        {
            dis[points[i]][points[k]] = mp[points[i]][points[k]];
            dis[points[k]][points[i]] = mp[points[k]][points[i]];
            sum += dis[points[i]][points[k]] + dis[points[k]][points[i]];
        }

        // Update the minimum distance of from i to k
        for (int kk = 0; kk < k; ++kk)
        {
            for (int i = 0; i < k; ++i)
            {
                if (ullong& curdis = dis[points[i]][points[k]], newdis = dis[points[i]][points[kk]] + dis[points[kk]][points[k]];
                    curdis > newdis)
                {
                    if (curdis == inf)
                        sum += newdis;
                    else
                        sum -= curdis - newdis;

                    curdis = newdis;
                }
            }
        }

        // Update the minimum distance of from k to i
        for (int kk = 0; kk < k; ++kk)
        {
            for (int i = 0; i < k; ++i)
            {
                if (ullong& curdis = dis[points[k]][points[i]], newdis = dis[points[k]][points[kk]] + dis[points[kk]][points[i]];
                    curdis > newdis)
                {
                    if (curdis == inf)
                        sum += newdis;
                    else
                        sum -= curdis - newdis;

                    curdis = newdis;
                }
            }
        }

        // Update the minimum distance of from i to j
        for (int i = 0; i < k; ++i)
        {
            for (int j = 0; j < k; ++j)
            {
                if (ullong& curdis = dis[points[i]][points[j]], newdis = dis[points[i]][points[k]] + dis[points[k]][points[j]];
                    curdis > newdis)
                {
                    if (curdis == inf)
                        sum += newdis;
                    else
                        sum -= curdis - newdis;

                    curdis = newdis;
                }
            }
        }

        ans[k] = sum;
    }

    for (int i = n - 1; i >= 0; --i)
        std::cout << ans[i] << ' ';

    return 0;
}