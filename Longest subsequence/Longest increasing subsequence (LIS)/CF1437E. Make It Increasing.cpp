/**
 * Educational Codeforces Round 97 (Rated for Div. 2)
 *
 * => E. Make It Increasing ( @c 2200 )
 *
 * -> https://codeforces.com/contest/1437/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/1437/submission/330801977 By huanhuanonly
 *
 * @b Binary-search for @a longest-increasing-subsequence
 *
 * ----July 25, 2025 [19h:52m:22s]----
*/

/// @brief This is an @c interesting problem!

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

    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n + 2);
    a.front() = std::numeric_limits<int>::min();
    a.back()  = std::numeric_limits<int>::max();

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
    }

    std::vector<int> b(k);

    for (int i = 0; i < k; ++i)
    {
        std::cin >> b[i];
    }

    bool yes = true;

    for (int i = 1; i < k; ++i)
    {
        yes = yes and (a[b[i - 1]] + (b[i] - b[i - 1]) <= a[b[i]]);
    }

    if (not yes)
    {
        std::cout << -1;
    }
    else
    {
        auto get = [&](int l, int r) -> int
        {
            auto check = [&a, l, r](int i) -> bool
            {
                return a[l] + (i - l) <= a[i] and a[i] + (r - i) <= a[r];
            };

            ++l, --r;

            if (l > r)
            {
                return 0;
            }

            std::vector<int> v;

            for (int i = l; i <= r; ++i)
            {
                if (check(i))
                {
                    int x = a[i] - (i - l);

                    if (auto it = std::ranges::upper_bound(v, x); it != v.end())
                    {
                        *it = x;
                    }
                    else
                    {
                        v.push_back(x);
                    }
                }
            }

            return (r - l + 1) - static_cast<int>(v.size());
        };

        int ans = 0;

        for (int i = 1; i < k; ++i)
        {
            ans += get(b[i - 1], b[i]);
        }

        if (k)
        {
            ans += get(0, b.front());
            ans += get(b.back(), n + 1);
        }
        else
        {
            ans += get(0, n + 1);
        }

        std::cout << ans;
    }

    return 0;
}