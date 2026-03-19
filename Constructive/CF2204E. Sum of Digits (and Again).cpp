/**
 * Educational Codeforces Round 188 (Rated for Div. 2)
 * 
 * => E. Sum of Digits (and Again) ( @c Rating )
 * 
 * -> https://codeforces.com/contest/2204/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2204/submission/367193352 By huanhuanonly
 * 
 * @b Constructive
 * 
 * ----March 18, 2026 [14h:42m:52s]----
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
        std::string s;
        std::cin >> s;

        std::array<int, 10> cnt{};

        for (const char& c : s)
        {
            ++cnt[c - '0'];
        }

        auto csum = [&]() -> int
        {
            int res = 0;

            for (int i = 1; i < cnt.size(); ++i)
            {
                res += cnt[i] * i;
            }

            return res;
        };

        auto $ = [](int x) -> int
        {
            int s = 0;

            for (; x; x /= 10)
            {
                s += x % 10;
            }

            return s;
        };

        std::string ans;

        auto push = [&](const auto& self, int x) -> bool
        {
            std::array<int, 10> c{};

            for (int td = x; td; td /= 10)
            {
                ++c[td % 10];
            }

            for (int i = 0; i < c.size(); ++i)
            {
                if (cnt[i] < c[i])
                {
                    return false;
                }
            }

            for (int i = 0; i < c.size(); ++i)
            {
                cnt[i] -= c[i];
            }

            ans += std::to_string(x);
            bool yes = x <= 9 ? true : self(self, $(x));

            for (int i = 0; i < c.size(); ++i)
            {
                cnt[i] += c[i];
            }

            return yes;
        };

        for (int i = 1; i <= 900000; ++i)
        {
            ans.clear();

            if (bool yes = push(push, i))
            {
                for (const char& c : ans)
                {
                    if (--cnt[c - '0'] < 0)
                    {
                        yes = false;
                    }
                }

                if (yes and csum() == i or csum() == 0)
                {
                    for (int j = 9; j >= 0; --j)
                    {
                        std::cout << std::string(cnt[j], '0' + j);
                    }
                    
                    std::cout << ans << '\n';
                    break;
                }

                for (const char& c : ans)
                {
                    ++cnt[c - '0'];
                }
            }
        }
    }

    return 0;
}