/**
 * 牛客小白月赛128
 * 
 * => E-扫雷难度调节 ( @c 1800 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/127265/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=81847298 By huanhuanonly
 * 
 * @b Constructive
 * 
 * ----January 30, 2026 [22h:11m:13s]----
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
        int n, m, k;
        std::cin >> n >> m >> k;
        
        auto test = [](int n, int m, int k, auto output) -> bool
        {
            int kk = k;

            std::vector mp(n, std::string(m, '1'));
    
            std::vector<bool> filled(n + 1);
    
            auto fill_line1 = [&](int i) -> void
            {
                filled[i] = true;
    
                for (int j = 0; j < m and k; ++j, --k)
                {
                    mp[i][j] = '0';
                }
            };
    
            auto fill_line2 = [&](int i) -> void
            {
                if (m != 1)
                {
                    if (k)
                    {
                        mp[i][0] = '0';
                        --k;
                    }

                    for (int j = 2; j < m and k; j += 3)
                    {
                        mp[i][j] = '0';
                        --k;

                        if (k and j + 2 < m)
                        {
                            mp[i][j + 1] = '0';
                            --k;
                        }
                    }
                }
            };
    
            if (n != 1)
            {
                fill_line1(0);
            }
    
            for (int i = 2; i < n; i += 3)
            {
                fill_line1(i);
    
                if (i + 2 < n)
                {
                    fill_line1(i + 1);
                }
            }
    
            for (int i = 0; i < n; ++i)
            {
                if (not filled[i])
                {
                    fill_line2(i);
                }
            }

            if (k)
            {
                return false;
            }
            else
            {
                assert([&]() -> bool
                {
                    for (int i = 0; i < n; ++i)
                    {
                        kk -= std::ranges::count(mp[i], '0');
                    }

                    return kk == 0;
                }());

                output(mp);
                return true;
            }
        };

        if (k >= n * m)
        {
            std::cout << -1 << '\n';
        }
        else if (not test(n, m, k, [](const auto& mp) -> void {
                for (int i = 0; i < mp.size(); ++i)
                {
                    std::cout << mp[i] << '\n';
                }
            }) and not test(m, n, k, [](const auto& mp) -> void {
                for (int j = 0; j < mp.front().size(); ++j)
                {
                    for (int i = 0; i < mp.size(); ++i)
                    {
                        std::cout.put(mp[i][j]);
                    }

                    std::cout.put('\n');
                }
            }))
        {
            std::cout << -1 << '\n';
        }
    }

    return 0;
}