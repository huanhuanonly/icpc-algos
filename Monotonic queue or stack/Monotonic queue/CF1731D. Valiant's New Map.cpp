/**
 * Codeforces Round 841 (Div. 2) and Divide by Zero 2022
 *
 * => D. Valiant's New Map ( @c 1700 )
 *
 * -> https://codeforces.com/contest/1731/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/1731/submission/343821890 By huanhuanonly
 *
 * @b Binary-search and @b Monotonic-queue ( @a sliding-window )
 *
 * ----October 15, 2025 [15h:53m:21s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, m;
        std::cin >> n >> m;

        std::vector v(n, std::vector<int>(m));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                std::cin >> v[i][j];
            }
        }

        std::vector pre(n, std::vector<int>(m));

        auto check = [&](int mid) -> bool
        {
            std::deque<int> que;

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    for (; not que.empty() and v[i][que.back()] > v[i][j]; que.pop_back());

                    que.push_back(j);

                    for (; not que.empty() and que.front() <= j - mid; que.pop_front());

                    pre[i][j] = v[i][que.front()];
                }

                que.clear();
            }

            for (int j = mid - 1; j < m; ++j)
            {
                for (int i = 0; i < n; ++i)
                {
                    for (; not que.empty() and pre[que.back()][j] > pre[i][j]; que.pop_back());

                    que.push_back(i);

                    for (; not que.empty() and que.front() <= i - mid; que.pop_front());

                    if (i >= mid - 1 and pre[que.front()][j] >= mid)
                    {
                        return true;
                    }
                }

                que.clear();
            }

            return false;
        };

        int l = 1, r = std::min(n, m) + 1, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (check(mid))
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }

        std::cout << l << '\n';
    }

    return 0;
}