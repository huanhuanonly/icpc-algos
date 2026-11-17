/**
 * 2026 ICPC Nanchang Invitational and Jiangxi Provincial Collegiate Programming Contest
 *
 * => H. BABA BOOEY
 *
 * -> https://codeforces.com/gym/106551/problem/H
 *
 * Submissions ~> https://codeforces.com/gym/106551/submission/389997918 By huanhuanonly
 *
 * @b Game-theory
 *
 * ----September 09, 2026 [14h:20m:59s]----
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
        int n, k;
        std::cin >> n >> k;

        std::vector<int> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        bool alice = false;

        for (int b = 1; b <= k; b <<= 1)
        {
            int64 cnt = 0;

            for (int i : v)
            {
                cnt += i / b;
            }

            if (cnt & 1)
            {
                alice = true;
                break;
            }
        }

        if (alice)
        {
            std::cout << "Alice\n";
        }
        else
        {
            std::cout << "Bob\n";
        }
    }

    return 0;
}