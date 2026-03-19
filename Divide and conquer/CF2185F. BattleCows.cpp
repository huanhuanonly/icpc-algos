/**
 * Codeforces Round 1074 (Div. 4)
 * 
 * => F. BattleCows ( @c 1700 )
 * 
 * -> https://codeforces.com/contest/2185/problem/F
 * 
 * Submissions ~> https://codeforces.com/contest/2185/submission/358577660 By huanhuanonly
 * 
 * @b Dfs and @b Divide-and-conquer
 * @b Prefix-sum
 * 
 * ----January 18, 2026 [23h:41m:45s]----
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
        uint32 n, q;
        std::cin >> n >> q;

        std::vector<uint32> v((1 << n) + 1), pre((1 << n) + 1);

        for (uint32 i = 1; i < v.size(); ++i)
        {
            std::cin >> v[i];
        }

        std::partial_sum(v.begin(), v.end(), pre.begin(), std::bit_xor{});

        auto sum = [&](uint32 l, uint32 r) -> uint32
        {
            return pre[r] ^ pre[l - 1];
        };

        while (q--)
        {
            uint32 idx, c;
            std::cin >> idx >> c;

            auto dfs = [&](const auto& self, uint32 l, uint32 r) -> uint32
            {
                if (l == r)
                {
                    return 0;
                }

                const auto mid = l + r >> 1;

                if (idx <= mid)
                {
                    const auto res = self(self, l, mid);

                    if ((sum(l, mid) ^ v[idx] ^ c) < sum(mid + 1, r))
                    {
                        return res + (r - mid);
                    }
                    else
                    {
                        return res;
                    }
                }
                else
                {
                    const auto res = self(self, mid + 1, r);

                    if ((sum(mid + 1, r) ^ v[idx] ^ c) <= sum(l, mid))
                    {
                        return res + (mid - l + 1);
                    }
                    else
                    {
                        return res;
                    }
                }
            };

            std::cout << dfs(dfs, 1, 1 << n) << '\n';
        }
    }

    return 0;
}