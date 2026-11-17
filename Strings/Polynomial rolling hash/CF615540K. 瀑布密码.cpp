/**
 * 2025-2026 国际大学生程序设计竞赛贵州省赛
 *
 * => K. 瀑布密码
 *
 * -> https://codeforces.com/gym/615540/problem/K
 *
 * Submissions ~> https://codeforces.com/gym/615540/submission/385429376 By huanhuanonly
 *
 * @b Polynomial-rolling-hash
 *
 * ----August 03, 2026 [23h:29m:54s]----
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

    int n, m;
    std::cin >> n >> m;

    constexpr uint128 base = 998244353;

    std::vector<std::vector<uint128>> s(n), t(n);

    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;

        s[i].resize(str.size());
        t[i].resize(str.size());

        uint128 hash = 0;

        for (int j = 0; j < str.size(); ++j)
        {
            hash = s[i][j] = hash * base + str[j];
        }

        std::ranges::reverse(str);
        hash = 0;

        for (int j = 0; j < str.size(); ++j)
        {
            hash = t[i][j] = hash * base + str[j];
        }
    }

    while (m--)
    {
        int i, j;
        std::cin >> i >> j;

        --i, --j;

        int l = -1, r = std::min(s[i].size(), t[j].size()), mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (s[i][mid] == t[j][mid])
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }

        std::cout << l + 1 << '\n';
    }

    return 0;
}