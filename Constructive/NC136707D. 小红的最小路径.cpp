/**
 * 牛客周赛 Round 148
 *
 * => D-小红的最小路径 ( @c 1500 )
 *
 * -> https://ac.nowcoder.com/acm/contest/136707/D
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83862007 By huanhuanonly
 *
 * @b Constructive and @b Bitwise-XOR
 *
 * ----June 14, 2026 [19h:59m:30s]----
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

    uint64 l, r;
    std::cin >> l >> r;

    std::vector<uint64> ans{l};

    for (uint64 b = 60; b--; )
    {
        if ((l ^ r) & (1ULL << b))
        {
            l ^= 1ULL << b;
            ans.push_back(l);
        }
    }

    std::cout << ans.size() << '\n';

    for (int i = 0; i < ans.size(); ++i)
    {
        std::cout << ans[i] << ' ';
    }

    return 0;
}