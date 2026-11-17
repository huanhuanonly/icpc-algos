/**
 * 2024 Jiangsu Collegiate Programming Contest
 *
 * => K. Number Deletion Game
 *
 * -> https://codeforces.com/gym/105161/problem/K
 *
 * Submissions ~> https://codeforces.com/gym/105161/submission/389004434 By huanhuanonly
 *
 * @b Game-theory
 *
 * ----August 31, 2026 [21h:53m:08s]----
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

    std::map<int, int, std::ranges::greater> cnt;

    for (int i = 0, v; i < n; ++i)
    {
        std::cin >> v;
        ++cnt[v];
    }

    if (cnt.begin()->second & 1)
    {
        std::cout << "Alice\n";
    }
    else
    {
        std::cout << "Bob\n";
    }

    return 0;
}