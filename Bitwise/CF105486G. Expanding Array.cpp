/**
 * 2024 ICPC Asia Chengdu Regional Contest (The 3rd Universal Cup. Stage 15: Chengdu)
 *
 * => G. Expanding Array
 *
 * -> https://codeforces.com/gym/105486/problem/G
 *
 * Submissions ~> https://codeforces.com/gym/105486/submission/389195889 By huanhuanonly
 *
 * @b Bitwise-AND
 * @b Bitwise-XOR
 * @b Bitwise-OR
 *
 * ----September 02, 2026 [21h:05m:19s]----
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

    std::vector<uint32> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    std::set<uint32> set(v.begin(), v.end());

    for (int i = 1; i < n; ++i)
    {
        const auto a = v[i - 1], b = v[i];

        set.insert(a ^ b);
        set.insert(a & b);
        set.insert(a | b);


        set.insert((a & b) & a);
        set.insert((a & b) & b);
        set.insert((a & b) ^ a);
        set.insert((a & b) ^ b);
        set.insert((a & b) | a);
        set.insert((a & b) | b);

        set.insert((a ^ b) & a);
        set.insert((a ^ b) & b);
        set.insert((a ^ b) ^ a);
        set.insert((a ^ b) ^ b);
        set.insert((a ^ b) | a);
        set.insert((a ^ b) | b);

        set.insert((a | b) & a);
        set.insert((a | b) & b);
        set.insert((a | b) ^ a);
        set.insert((a | b) ^ b);
        set.insert((a | b) | a);
        set.insert((a | b) | b);


        set.insert(((a & b) & a) & a);
        set.insert(((a & b) & b) & a);
        set.insert(((a & b) ^ a) & a);
        set.insert(((a & b) ^ b) & a);
        set.insert(((a & b) | a) & a);
        set.insert(((a & b) | b) & a);

        set.insert(((a ^ b) & a) & a);
        set.insert(((a ^ b) & b) & a);
        set.insert(((a ^ b) ^ a) & a);
        set.insert(((a ^ b) ^ b) & a);
        set.insert(((a ^ b) | a) & a);
        set.insert(((a ^ b) | b) & a);

        set.insert(((a | b) & a) & a);
        set.insert(((a | b) & b) & a);
        set.insert(((a | b) ^ a) & a);
        set.insert(((a | b) ^ b) & a);
        set.insert(((a | b) | a) & a);
        set.insert(((a | b) | b) & a);

        set.insert(((a & b) & a) & b);
        set.insert(((a & b) & b) & b);
        set.insert(((a & b) ^ a) & b);
        set.insert(((a & b) ^ b) & b);
        set.insert(((a & b) | a) & b);
        set.insert(((a & b) | b) & b);

        set.insert(((a ^ b) & a) & b);
        set.insert(((a ^ b) & b) & b);
        set.insert(((a ^ b) ^ a) & b);
        set.insert(((a ^ b) ^ b) & b);
        set.insert(((a ^ b) | a) & b);
        set.insert(((a ^ b) | b) & b);

        set.insert(((a | b) & a) & b);
        set.insert(((a | b) & b) & b);
        set.insert(((a | b) ^ a) & b);
        set.insert(((a | b) ^ b) & b);
        set.insert(((a | b) | a) & b);
        set.insert(((a | b) | b) & b);

        set.insert(((a & b) & a) ^ a);
        set.insert(((a & b) & b) ^ a);
        set.insert(((a & b) ^ a) ^ a);
        set.insert(((a & b) ^ b) ^ a);
        set.insert(((a & b) | a) ^ a);
        set.insert(((a & b) | b) ^ a);

        set.insert(((a ^ b) & a) ^ a);
        set.insert(((a ^ b) & b) ^ a);
        set.insert(((a ^ b) ^ a) ^ a);
        set.insert(((a ^ b) ^ b) ^ a);
        set.insert(((a ^ b) | a) ^ a);
        set.insert(((a ^ b) | b) ^ a);

        set.insert(((a | b) & a) ^ a);
        set.insert(((a | b) & b) ^ a);
        set.insert(((a | b) ^ a) ^ a);
        set.insert(((a | b) ^ b) ^ a);
        set.insert(((a | b) | a) ^ a);
        set.insert(((a | b) | b) ^ a);

        set.insert(((a & b) & a) ^ b);
        set.insert(((a & b) & b) ^ b);
        set.insert(((a & b) ^ a) ^ b);
        set.insert(((a & b) ^ b) ^ b);
        set.insert(((a & b) | a) ^ b);
        set.insert(((a & b) | b) ^ b);

        set.insert(((a ^ b) & a) ^ b);
        set.insert(((a ^ b) & b) ^ b);
        set.insert(((a ^ b) ^ a) ^ b);
        set.insert(((a ^ b) ^ b) ^ b);
        set.insert(((a ^ b) | a) ^ b);
        set.insert(((a ^ b) | b) ^ b);

        set.insert(((a | b) & a) ^ b);
        set.insert(((a | b) & b) ^ b);
        set.insert(((a | b) ^ a) ^ b);
        set.insert(((a | b) ^ b) ^ b);
        set.insert(((a | b) | a) ^ b);
        set.insert(((a | b) | b) ^ b);

        set.insert(((a & b) & a) | a);
        set.insert(((a & b) & b) | a);
        set.insert(((a & b) ^ a) | a);
        set.insert(((a & b) ^ b) | a);
        set.insert(((a & b) | a) | a);
        set.insert(((a & b) | b) | a);

        set.insert(((a ^ b) & a) | a);
        set.insert(((a ^ b) & b) | a);
        set.insert(((a ^ b) ^ a) | a);
        set.insert(((a ^ b) ^ b) | a);
        set.insert(((a ^ b) | a) | a);
        set.insert(((a ^ b) | b) | a);

        set.insert(((a | b) & a) | a);
        set.insert(((a | b) & b) | a);
        set.insert(((a | b) ^ a) | a);
        set.insert(((a | b) ^ b) | a);
        set.insert(((a | b) | a) | a);
        set.insert(((a | b) | b) | a);

        set.insert(((a & b) & a) | b);
        set.insert(((a & b) & b) | b);
        set.insert(((a & b) ^ a) | b);
        set.insert(((a & b) ^ b) | b);
        set.insert(((a & b) | a) | b);
        set.insert(((a & b) | b) | b);

        set.insert(((a ^ b) & a) | b);
        set.insert(((a ^ b) & b) | b);
        set.insert(((a ^ b) ^ a) | b);
        set.insert(((a ^ b) ^ b) | b);
        set.insert(((a ^ b) | a) | b);
        set.insert(((a ^ b) | b) | b);

        set.insert(((a | b) & a) | b);
        set.insert(((a | b) & b) | b);
        set.insert(((a | b) ^ a) | b);
        set.insert(((a | b) ^ b) | b);
        set.insert(((a | b) | a) | b);
        set.insert(((a | b) | b) | b);
    }

    std::cout << set.size() << '\n';

    return 0;
}