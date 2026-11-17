/**
 * The 2025 ICPC Asia Shenyang Regional Contest (The 4th Universal Cup. Stage 6: Grand Prix of Shenyang)
 *
 * => M. The End?
 *
 * -> https://codeforces.com/gym/106252/problem/M
 *
 * Submissions ~> https://codeforces.com/gym/106252/submission/389360210 By huanhuanonly
 *
 * @b Probability-theory
 * @b Divide-and-conquer
 *
 * ----September 04, 2026 [20h:55m:09s]----
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

    std::vector<std::tuple<real80, real80, int>> v(8);

    for (int i = 0; i < v.size(); ++i)
    {
        auto& [a, b, id] = v[i];
        std::cin >> a >> b;

        id = i;
    }

    std::ranges::sort(v);

    real80 max = 0;

    do
    {
        std::vector<real80> p(8, 1);

        auto dfs = [&](const auto& self, int l, int r) -> void
        {
            if (l == r)
            {
                return;
            }

            const auto mid = l + r >> 1;

            self(self, l, mid);
            self(self, mid + 1, r);

            std::vector<real80> t(8);

            for (int i = l; i <= mid; ++i)
            {
                for (int j = mid + 1; j <= r; ++j)
                {
                    const auto a = std::get<0>(v[i]);
                    const auto b = std::get<1>(v[j]);

                    t[i] += p[i] * p[j] * (a / (a + b));
                }
            }

            for (int i = mid + 1; i <= r; ++i)
            {
                for (int j = l; j <= mid; ++j)
                {
                    const auto a = std::get<1>(v[i]);
                    const auto b = std::get<0>(v[j]);

                    t[i] += p[i] * p[j] * (a / (a + b));
                }
            }

            std::copy(t.begin() + l, t.begin() + r + 1, p.begin() + l);
        };

        dfs(dfs, 0, 7);

        max = std::max(max, p[std::ranges::find(v, 0, [](const auto& t) { return std::get<2>(t); }) - v.begin()]);
    } while (std::ranges::next_permutation(v).found);

    std::cout << std::fixed << std::setprecision(12) << max << '\n';

    return 0;
}