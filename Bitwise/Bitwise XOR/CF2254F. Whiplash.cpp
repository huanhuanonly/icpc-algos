/**
 * Codeforces Round 1114 (Div. 3)
 *
 * => F. Whiplash ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2254/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/2254/submission/388271835 By huanhuanonly
 *
 * @b Bitwise-XOR
 *
 * ----August 25, 2026 [01h:23m:57s]----
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
        int n;
        std::cin >> n;

        std::vector<uint32> a(n), b(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> a[i];
        }

        for (int i = 0; i < n; ++i)
        {
            std::cin >> b[i];
        }

        std::ranges::sort(a);
        std::ranges::sort(b);

        if (a == b)
        {
            std::cout << "YES\n";
            continue;
        }

        std::array<uint32, 30> ca{}, cb{};

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < ca.size(); ++j)
            {
                if (a[i] & (1U << j))
                {
                    ++ca[j];
                }

                if (b[i] & (1U << j))
                {
                    ++cb[j];
                }
            }
        }

        bool yes = false;

        for (const auto& v : std::set(a.begin(), a.end()))
        {
            bool flag = true;

            for (int i = 0; i < ca.size(); ++i)
            {
                const uint32 cnt = (v & 1U << i ? n - ca[i] + 1 : ca[i]);

                if (cnt != cb[i])
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
            {
                auto t = a | std::views::transform([v](uint32 i) -> uint32 { return i ^ v; }) | std::ranges::to<std::vector>();
                *std::ranges::find(t, 0) = v;

                std::ranges::sort(t);

                if (t == b)
                {
                    yes = true;
                    break;
                }
            }
        }

        if (yes)
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}