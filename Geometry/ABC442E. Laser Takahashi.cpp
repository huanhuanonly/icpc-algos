/**
 * JPRS Programming Contest 2026#1 (AtCoder Beginner Contest 442)
 * 
 * => E - Laser Takahashi ( @c 450 )
 * 
 * -> https://atcoder.jp/contests/abc442/tasks/abc442_e
 * 
 * Submissions ~> https://atcoder.jp/contests/abc442/submissions/72723202 By huanhuanonly
 * 
 * @b Geometry ( @a polar-angle-sort ) and @b Prefix-sum
 * 
 * ----January 24, 2026 [22h:15m:25s]----
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

    int64 n, q;
    std::cin >> n >> q;

    std::map<real128, std::vector<int64>, std::ranges::greater> mp;

    for (int64 i = 1; i <= n; ++i)
    {
        int64 x, y;
        std::cin >> x >> y;

        mp[::atan2l(y, x)].push_back(i);
    }

    std::vector<int64> pre;
    pre.reserve(1 + mp.size());
    pre.push_back(0);

    std::vector<int64> pos(n + 1);

    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        pre.push_back(pre.back() + it->second.size());

        for (const int64& i : it->second)
        {
            pos[i] = pre.size() - 1;
        }
    }

    while (q--)
    {
        int64 s, t;
        std::cin >> s >> t;

        s = pos[s], t = pos[t];

        if (s <= t)
        {
            std::cout << pre[t] - pre[s - 1] << '\n';
        }
        else
        {
            std::cout << pre.back() - pre[s - 1] + pre[t] << '\n';
        }
    }

    return 0;
}