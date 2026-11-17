/**
 * Squarepoint Challenge (Codeforces Round 1055, Div. 1 + Div. 2)
 * 
 * => F. Triple Attack ( @c 2500 )
 * 
 * -> https://codeforces.com/contest/2152/problem/F
 * 
 * Submissions ~> https://codeforces.com/contest/2152/submission/343893699 By huanhuanonly
 * 
 * @b Binary-lifting and @b Lowest-common-ancestor
 * 
 * ----October 15, 2025 [23h:53m:17s]----
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

    constexpr int laycnt = 19;

    std::array<int, laycnt> pow2{1};

    for (int i = 1; i < laycnt; ++i)
    {
        pow2[i] = pow2[i - 1] * 2;
    }

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, z;
        std::cin >> n >> z;

        std::vector<int> v(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
        }

        std::vector<int> depth(n + 2);

        std::vector<std::array<int, laycnt>> next1(n + 2);
        std::vector<std::array<std::pair<int, int>, laycnt>> next2(n + 2);

        next1[n + 1].fill(n + 1);
        
        next2[n].fill({n + 1, 0});
        next2[n + 1].fill({n + 1, 0});

        for (int i = n; i >= 1; --i)
        {
            next1[i][0] = std::max(int(std::ranges::upper_bound(v, v[i] + z) - v.begin()), std::min(i + 2, n + 1));
            depth[i] = depth[next1[i][0]] + 1;
        }

        for (int lay = 1; lay < laycnt; ++lay)
        {
            for (int i = 1; i <= n; ++i)
            {
                next1[i][lay] = next1[next1[i][lay - 1]][lay - 1];
            }
        }

        for (int i = 1; i < n; ++i)
        {
            int a = i, b = i + 1;

            for (int k = 0, diff = depth[a] - depth[b]; k <= laycnt; ++k)
            {
                if (diff & (1 << k))
                {
                    next2[i][0].second += pow2[k];
                    a = next1[a][k];
                }
            }

            for (int lay = laycnt - 1; lay >= 0; --lay)
            {
                if (next1[a][lay] != next1[b][lay])
                {
                    next2[i][0].second += pow2[lay] * 2;

                    a = next1[a][lay];
                    b = next1[b][lay];
                }
            }
            
            next2[i][0].first = next1[a][0];
            next2[i][0].second += 2;
        }

        for (int lay = 1; lay < laycnt; ++lay)
        {
            for (int i = 1; i < n; ++i)
            {
                next2[i][lay].first = next2[next2[i][lay - 1].first][lay - 1].first;
                next2[i][lay].second = next2[i][lay - 1].second + next2[next2[i][lay - 1].first][lay - 1].second;
            }
        }

        int q;
        std::cin >> q;

        while (q--)
        {
            int l, r;
            std::cin >> l >> r;

            const int len = r - l + 1;

            if (len <= 2)
            {
                std::cout << len << '\n';
            }
            else
            {
                int cnt = 2;

                int a = l, b;

                for (int lay = laycnt - 1; lay >= 0; --lay)
                {
                    if (next2[a][lay].first <= r)
                    {
                        cnt += next2[a][lay].second;
                        a = next2[a][lay].first;
                    }
                }

                if (a == r)
                {
                    std::cout << cnt - 1 << '\n';
                    continue;
                }
                
                b = a + 1;

                for (int lay = laycnt - 1; lay >= 0; --lay)
                {
                    if (next1[a][lay] <= r)
                    {
                        cnt += pow2[lay];
                        a = next1[a][lay];
                    }

                    if (next1[b][lay] <= r)
                    {
                        cnt += pow2[lay];
                        b = next1[b][lay];
                    }
                }

                std::cout << cnt << '\n';
            }
        }
    }

    return 0;
}