/**
 * Testing Round 20 (Unrated, Communication Problems)
 * 
 * => C. Intercepting Butterflies
 * 
 * -> https://codeforces.com/contest/2168/problem/C
 * 
 * Submissions ~> https://codeforces.com/contest/2168/submission/347337109 By huanhuanonly
 * 
 * @b Run-twice ( @a communication )
 * @b Bitmasks and @b Hamming-code
 * 
 * @see also https://en.wikipedia.org/wiki/Hamming_code
 * 
 * ----November 04, 2025 [10h:32m:19s]----
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

    std::string type;
    std::cin >> type;

    int _;
    std::cin >> _;

    if (type == "first") while (_--)
    {
        uint32 x;
        std::cin >> x;

        std::array<uint8, 20> bits{};

        for (int i = 0; i < 15; ++i)
        {
            if ((x - 1 >> i) & 1)
            {
                bits[i] = true;
            }
        }

        for (int j = 0; j < 4; ++j)
        {
            for (int i = 1; i <= 15; ++i)
            {
                if ((i >> j) & 1)
                {
                    bits[15 + j] ^= bits[i - 1];
                }
            }
        }
        
        bits[19] = bits[18] ^ bits[17] ^ bits[16] ^ bits[15];

        std::cout << static_cast<int>(std::reduce(bits.begin(), bits.end())) << '\n';

        for (int i = 0; i < 20; ++i)
        {
            if (bits[i])
            {
                std::cout << i + 1 << ' ';
            }
        }

        std::cout.put('\n');
    }
    else while (_--)
    {
        int n;
        std::cin >> n;

        std::array<uint8, 20> bits{};

        for (int i = 0, s; i < n; ++i)
        {
            std::cin >> s;
            bits[s - 1] = true;
        }

        if (bits[19] == (bits[18] ^ bits[17] ^ bits[16] ^ bits[15]))
        {
            uint32 pos = 0;

            for (int j = 0; j < 4; ++j)
            {
                uint32 sum = 0;
                for (int i = 1; i <= 15; ++i)
                {
                    if ((i >> j) & 1)
                    {
                        sum ^= bits[i - 1];
                    }
                }

                if (sum != bits[15 + j])
                {
                    pos |= 1U << j;
                }
            }

            if (pos)
            {
                bits[pos - 1] ^= 1;
            }
        }

        uint32 x = 0;

        for (int i = 0; i < 15; ++i)
        {
            if (bits[i])
            {
                x |= 1U << i;
            }
        }

        std::cout << x + 1 << '\n';
    }

    return 0;
}