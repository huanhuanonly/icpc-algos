/**
 * 2024 ICPC Asia Chengdu Regional Contest (The 3rd Universal Cup. Stage 15: Chengdu)
 *
 * => I. Good Partitions
 *
 * -> https://codeforces.com/gym/105486/problem/I
 *
 * Submissions ~> https://codeforces.com/gym/105486/submission/389202580 By huanhuanonly
 *
 * @b Number-theory ( @a divisor )
 *
 * ----September 02, 2026 [23h:50m:44s]----
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
        int n, q;
        std::cin >> n >> q;

        std::vector<uint32> v(n + 2);
        v.back() = std::numeric_limits<uint32>::max();

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
        }

        int size = 0;

        std::vector<int> cnt(n + 1);
        std::vector<int> tot(n + 1);

        tot[0] = n;

        auto insert = [&](int x) -> void
        {
            ++size;

            for (int i = 1, sq = std::sqrt(x); i <= sq; ++i)
            {
                if (x % i == 0)
                {
                    --tot[cnt[i]];
                    ++cnt[i];
                    ++tot[cnt[i]];

                    if (i != x / i)
                    {
                        --tot[cnt[x / i]];
                        ++cnt[x / i];
                        ++tot[cnt[x / i]];
                    }
                }
            }
        };

        auto remove = [&](int x) -> void
        {
            --size;

            for (int i = 1, sq = std::sqrt(x); i <= sq; ++i)
            {
                if (x % i == 0)
                {
                    --tot[cnt[i]];
                    --cnt[i];
                    ++tot[cnt[i]];

                    if (i != x / i)
                    {
                        --tot[cnt[x / i]];
                        --cnt[x / i];
                        ++tot[cnt[x / i]];
                    }
                }
            }
        };

        for (int i = 1; i <= n; ++i)
        {
            if (v[i] > v[i + 1])
            {
                insert(i);
            }
        }

        std::cout << tot[size] << '\n';

        while (q--)
        {
            uint32 p, x;
            std::cin >> p >> x;

            if (v[p] > v[p + 1])
            {
                remove(p);
            }

            if (v[p - 1] > v[p])
            {
                remove(p - 1);
            }

            v[p] = x;

            if (v[p] > v[p + 1])
            {
                insert(p);
            }

            if (v[p - 1] > v[p])
            {
                insert(p - 1);
            }

            std::cout << tot[size] << '\n';
        }
    }

    return 0;
}