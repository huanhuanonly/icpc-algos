/**
 * Codeforces Round 1054 (Div. 3)
 *
 * => G. Buratsuta 3 ( @c 2100 )
 *
 * -> https://codeforces.com/contest/2149/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/2149/submission/340569914 By huanhuanonly
 *
 * @b Monte-Carlo-algorithm
 *
 * ----September 26, 2025 [14h:42m:39s]----
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
        int n, q;
        std::cin >> n >> q;

        std::vector<int> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        auto s = v;
        std::ranges::sort(s);
        s.erase(std::ranges::unique(s).begin(), s.end());

        std::vector<std::vector<int>> pos(n);

        for (int i = 0; i < n; ++i)
        {
            v[i] = std::ranges::lower_bound(s, v[i]) - s.begin();
            pos[v[i]].push_back(i);
        }

        auto count = [&](int value, int l, int r) -> int
        {
            const auto& ref = pos[value];

            const auto li = std::ranges::lower_bound(ref, l);
            const auto ri = std::ranges::upper_bound(ref, r);

            return ri - li;
        };

        static std::mt19937 rng(std::random_device{}());

        std::set<int> ans;

        while (q--)
        {
            int l, r;
            std::cin >> l >> r;

            --l, --r;

            std::uniform_int_distribution<int> ud(l, r);

            const int len = r - l + 1;

            for (int i = 0; i < 40; ++i)
            {
                const int value = v[ud(rng)];

                if (count(value, l, r) > len / 3)
                {
                    ans.insert(s[value]);
                }
            }

            if (ans.empty())
            {
                std::cout << -1 << '\n';
            }
            else
            {
                for (int i : ans)
                {
                    std::cout << i << ' ';
                }

                std::cout.put('\n');
                ans.clear();
            }
        }
    }

    return 0;
}