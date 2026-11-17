/**
 * The 2025 ICPC Asia Shenyang Regional Contest (The 4th Universal Cup. Stage 6: Grand Prix of Shenyang)
 *
 * => K. Relay Jump
 *
 * -> https://codeforces.com/gym/106252/problem/K
 *
 * Submissions ~> https://codeforces.com/gym/106252/submission/389388565 By huanhuanonly
 *
 * @b Geometry
 *
 * ----September 05, 2026 [01h:39m:44s]----
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

    int n, s;
    std::cin >> n >> s;

    --s;

    struct item
    {
        int64 px, py, qx, qy;
    };

    std::vector<item> v(n);

    int64 spx = 0, spy = 0;
    int64 sqx = 0, sqy = 0;

    for (auto& [px, py, qx, qy] : v)
    {
        std::cin >> px >> py >> qx >> qy;

        spx += px;
        spy += py;
        sqx += qx;
        sqy += qy;
    }

    for (int i = 0; i < n; ++i)
    {
        if (spx - 2 * v[s].px == sqx - 2 * v[i].qx and spy - 2 * v[s].py == sqy - 2 * v[i].qy)
        {
            std::cout << 1 + i << '\n';
            break;
        }
    }

    return 0;
}