/**
 * 牛客周赛 Round 148
 *
 * => E-小芳的数组操作 ( @c 1600 )
 *
 * -> https://ac.nowcoder.com/acm/contest/136707/E
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83858510 By huanhuanonly
 *
 * @b Bitwise-XOR
 *
 * ----June 14, 2026 [19h:36m:11s]----
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

    int n;
    std::cin >> n;

    std::vector<uint64> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    int64 ans = 0;

    for (uint64 b = 0; b < 35; ++b)
    {
        std::vector<int64> pos;
        pos.reserve(n);

        for (int i = 0; i < n; ++i)
        {
            if (v[i] & (1ULL << b))
            {
                pos.push_back(i);
            }
        }

        if (pos.size() & 1)
        {
            ans = -1;
            break;
        }

        if (pos.empty())
        {
            continue;
        }

        int64 ca = 0, cb = pos.front() + (n - pos.back());

        for (int i = 1; i < pos.size(); i += 2)
        {
            ca += pos[i] - pos[i - 1];
        }

        for (int i = 2; i < pos.size() - 1; i += 2)
        {
            cb += pos[i] - pos[i - 1];
        }

        ans += std::min(ca, cb);
    }

    std::cout << ans << '\n';

    return 0;
}