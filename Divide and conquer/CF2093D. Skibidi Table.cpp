/**
 * Codeforces Round 1016 (Div. 3)
 *
 * => D. Skibidi Table ( @c 1400 )
 *
 * -> https://codeforces.com/contest/2093/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/2093/submission/314953915 By huanhuanonly
 *
 * @b Divide-and-conquer
 *
 * ----April 11, 2025 [13h:46m:04s]----
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

uint64 find(uint64 n, uint64 x, uint64 y, const std::pair<uint64, uint64>& range)
{
    if (n == 1)
    {
        return range.first;
    }

    uint64 diff = range.second - range.first + 1;

    if (x <= n / 2)
    {
        if (y <= n / 2)
        {
            return find(n / 2, x, y, { range.first, range.second - diff / 4 * 3 });
        }
        else
        {
            return find(n / 2, x, y - n / 2, { range.first + diff / 4 * 3, range.second });
        }
    }
    else
    {
        if (y > n / 2)
        {
            return find(n / 2, x - n / 2, y - n / 2, { range.first + diff / 4 * 1, range.second - diff / 4 * 2 });
        }
        else
        {
            return find(n / 2, x - n / 2, y, { range.first + diff / 4 * 2, range.second - diff / 4 * 1});
        }
    }
}

void find(uint64 n, uint64 value, const std::pair<uint64, uint64>& range,
    std::pair<uint64, uint64>& x, std::pair<uint64, uint64>& y)
{
    if (n == 1)
    {
        return;
    }

    uint64 diff = range.second - range.first + 1;

    if (value < range.first + diff / 4 * 1)
    {
        x.second -= (x.second - x.first + 1) / 2; y.second -= (y.second - y.first + 1) / 2;

        find(n / 2, value, {range.first, range.second - diff / 4 * 3}, x, y);
    }
    else if (value < range.first + diff / 4 * 2)
    {
        x.first += (x.second - x.first + 1) / 2; y.first += (y.second - y.first + 1) / 2;

        find(n / 2, value, { range.first + diff / 4 * 1, range.second - diff / 4 * 2 }, x, y);
    }
    else if (value < range.first + diff / 4 * 3)
    {
        x.first += (x.second - x.first + 1) / 2; y.second -= (y.second - y.first + 1) / 2;

        find(n / 2, value, { range.first + diff / 4 * 2, range.second - diff / 4 * 1}, x, y);
    }
    else
    {
        x.second -= (x.second - x.first + 1) / 2; y.first += (y.second - y.first + 1) / 2;

        find(n / 2, value, { range.first + diff / 4 * 3, range.second }, x, y);
    }
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        uint64 n, q;
        std::cin >> n >> q;

        std::string s;
        while (q--)
        {
            std::cin >> s;

            if (s == "->")
            {
                uint64 x, y;
                std::cin >> x >> y;

                std::cout << find(1ull << n, x, y, { 1ull, 1ull << (n << 1ull) }) << '\n';
            }
            else
            {
                uint64 d;
                std::cin >> d;

                std::pair<uint64, uint64> x = { 1ull, 1ull << n };
                std::pair<uint64, uint64> y = { 1ull, 1ull << n };

                find(1ull << n, d, { 1ull, 1ull << (n << 1ull) }, x, y);

                std::cout << x.first << ' ' << y.first << '\n';
            }
        }
    }

    return 0;
}