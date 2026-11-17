/**
 * The 2024 ICPC Asia Nanjing Regional Contest (The 3rd Universal Cup. Stage 16: Nanjing)
 *
 * => K. Strips
 *
 * -> https://codeforces.com/gym/105484/problem/K
 *
 * Submissions ~> https://codeforces.com/gym/105484/submission/389104113 By huanhuanonly
 *
 * @b Constructive
 *
 * ----September 01, 2026 [22h:08m:59s]----
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
        int64 n, m, k, w;
        std::cin >> n >> m >> k >> w;

        std::vector<int64> a(n), b(m);

        for (int64 i = 0; i < n; ++i)
        {
            std::cin >> a[i];
        }

        for (int64 i = 0; i < m; ++i)
        {
            std::cin >> b[i];
        }

        b.push_back(0);
        b.push_back(w + 1);

        std::ranges::sort(a);
        std::ranges::sort(b);

        std::vector<int64> pos;

        auto calc = [&](int64 l, int64 r) -> bool
        {
            if (l > r)
            {
                return true;
            }

            const int64 cp = pos.size() - 1;

            int64 maxr = 0;

            for (int64 i = std::ranges::lower_bound(a, l) - a.begin(); i < a.size() and a[i] <= r; ++i)
            {
                if (a[i] > maxr)
                {
                    maxr = a[i] + k - 1;
                    pos.push_back(a[i]);

                    if (maxr > r)
                    {
                        int64 diff = maxr - r;

                        for (int64 j = pos.size() - 1; j > cp; --j)
                        {
                            pos[j] -= diff;

                            if (j - 1 > cp)
                            {
                                diff = (pos[j - 1] + k - 1) - pos[j] + 1;

                                if (diff <= 0)
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }

                        return pos[cp + 1] >= l;
                    }
                }
            }

            return true;
        };

        bool yes = true;

        for (int64 i = 1; i < b.size(); ++i)
        {
            yes = yes and calc(b[i - 1] + 1, b[i] - 1);
        }

        if (yes)
        {
            std::cout << pos.size() << '\n';

            for (int64 i = 0; i < pos.size(); ++i)
            {
                std::cout << pos[i] << " \n"[i + 1 == pos.size()];
            }
        }
        else
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}