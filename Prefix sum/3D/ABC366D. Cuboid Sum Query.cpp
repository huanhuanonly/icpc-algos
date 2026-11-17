/**
 * AtCoder Beginner Contest 366
 *
 * => D - Cuboid Sum Query ( @c 400 )
 *
 * -> https://atcoder.jp/contests/abc366/tasks/abc366_d
 *
 * Submissions ~> https://atcoder.jp/contests/abc366/submissions/56622543 By huanhuanonly
 *
 * @b 3D-Prefix-Sum
 *
 * ----August 12, 2024 [11h:45m:38s]----
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

    int n;
    std::cin >> n;

    std::vector<std::vector<std::vector<int>>> v(n + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1)));
    std::vector<std::vector<std::vector<int>>> pre(n + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1)));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                std::cin >> v[i][j][k];

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                pre[i][j][k] = pre[i][j - 1][k] + pre[i][j][k - 1] - pre[i][j - 1][k - 1]
                    + pre[i - 1][j][k] - pre[i - 1][j - 1][k] - pre[i - 1][j][k - 1] + pre[i - 1][j - 1][k - 1]
                    + v[i][j][k];

    int q;
    std::cin >> q;

    while (q--)
    {
        int li, ri, lj, rj, lk, rk;
        std::cin >> li >> ri >> lj >> rj >> lk >> rk;

        int ans = pre[ri][rj][rk] - pre[ri][lj - 1][rk] - pre[ri][rj][lk - 1] + pre[ri][lj - 1][lk - 1]
            - (pre[li - 1][rj][rk] - pre[li - 1][lj - 1][rk] - pre[li - 1][rj][lk - 1] + pre[li - 1][lj - 1][lk - 1]);

        std::cout << ans << '\n';
    }

    return 0;
}