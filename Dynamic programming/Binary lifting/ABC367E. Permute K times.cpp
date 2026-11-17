/**
 * AtCoder Beginner Contest 367
 *
 * => E - Permute K times ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc367/tasks/abc367_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc367/submissions/56925269 By huanhuanonly
 *
 * @b Binary-lifting
 *
 * ----August 20, 2024 [18h:03m:42s]----
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

    ullong n, k;
    std::cin >> n >> k;

    std::vector<std::array<int, 62>> dp(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> dp[i][0];

    std::vector<int> a(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int j = 1; j < 62; ++j)
    {
        for (int i = 1; i <= n; ++i)
        {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        int now = i;

        for (int j = 0; j < 62; ++j)
        {
            if (k & (1ull << j))
            {
                now = dp[now][j];
            }
        }

        std::cout << a[now] << ' ';
    }

    return 0;
}