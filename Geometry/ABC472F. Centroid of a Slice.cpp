/**
 * AtCoder Beginner Contest 472
 *
 * => F - Centroid of a Slice ( @c 525 )
 *
 * -> https://atcoder.jp/contests/abc472/tasks/abc472_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc472/submissions/78638429 By huanhuanonly
 *
 * @b Geometry
 * @b Prefix-sum
 *
 * ----August 22, 2026 [21h:47m:35s]----
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

    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int64, int64>> p(n + n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> p[i].first >> p[i].second;
        p[i + n] = p[i];
    }

    std::vector<int64> a(n + n + 1), cx(n + n + 1), cy(n + n + 1);

    for (int i = 1; i < n + n; ++i)
    {
        a[i] = p[i].first * p[i + 1].second - p[i + 1].first * p[i].second;
        cx[i] = (p[i].first + p[i + 1].first) * (p[i].first * p[i + 1].second - p[i + 1].first * p[i].second);
        cy[i] = (p[i].second + p[i + 1].second) * (p[i].first * p[i + 1].second - p[i + 1].first * p[i].second);
    }

    std::partial_sum(a.begin(), a.end(), a.begin());
    std::partial_sum(cx.begin(), cx.end(), cx.begin());
    std::partial_sum(cy.begin(), cy.end(), cy.begin());

    std::cout << std::fixed << std::setprecision(12);

    while (q--)
    {
        int u, v;
        std::cin >> u >> v;

        if (u > v)
        {
            v += n;
        }

        int64 A = p[v].first * p[u].second - p[u].first * p[v].second;
        int64 Cx = (p[v].first + p[u].first) * (p[v].first * p[u].second - p[u].first * p[v].second);
        int64 Cy = (p[v].second + p[u].second) * (p[v].first * p[u].second - p[u].first * p[v].second);

        A += a[v - 1] - a[u - 1];
        Cx += cx[v - 1] - cx[u - 1];
        Cy += cy[v - 1] - cy[u - 1];

        std::cout << 1.L / (6.L * A / 2) * Cx << ' ' <<  1.L / (6.L * A / 2) * Cy << '\n';
    }

    return 0;
}