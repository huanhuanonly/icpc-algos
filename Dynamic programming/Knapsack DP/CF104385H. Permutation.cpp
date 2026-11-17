/**
 * 2023 (ICPC) Jiangxi Provincial Contest -- Official Contest
 *
 * => H. Permutation
 *
 * -> https://codeforces.com/gym/104385/problem/H
 *
 * Submissions ~> https://codeforces.com/gym/104385/submission/387925390 By huanhuanonly
 *
 * @b Knapsack-DP ( @a group-knapsack-problem-with-bitset-optimization )
 *
 * ----August 22, 2026 [02h:20m:23s]----
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
        int n;
        std::cin >> n;

        std::vector<int> p(n);

        for (auto& i : p)
        {
            std::cin >> i;
        }

        std::map<int, int> cnt;
        int last = 0;

        for (int i = 1, max = p.front(); i < n; ++i)
        {
            if (p[i] > max)
            {
                max = p[i];
                ++cnt[i - last];
                last = i;
            }
        }

        ++cnt[n - last];

        std::vector<int> set;

        for (auto&& [key, value] : cnt)
        {
            for (int k = 1; value >= k; set.push_back(key * k), value -= k, k <<= 1);

            if (value)
            {
                set.push_back(key * value);
            }
        }

        constexpr int maxs = 5e5 / 2;
        std::bitset<maxs + 1> bs;

        for (const auto& i : set)
        {
            if (i > n / 2)
            {
                continue;
            }

            bs |= bs << i;
            bs.set(i);
        }

        if (bs.test(n / 2))
        {
            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }
    }

    return 0;
}