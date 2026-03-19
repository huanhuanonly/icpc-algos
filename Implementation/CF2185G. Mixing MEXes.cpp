/**
 * Codeforces Round 1074 (Div. 4)
 * 
 * => G. Mixing MEXes ( @c 1800 )
 * 
 * -> https://codeforces.com/contest/2185/problem/G
 * 
 * Submissions ~> https://codeforces.com/contest/2185/submission/358613662 By huanhuanonly
 * 
 * @b Implementation
 * 
 * ----January 18, 2026 [00h:20m:52s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        uint64 n;
        std::cin >> n;

        std::vector<std::vector<uint64>> v(n);

        std::vector<std::vector<uint64>> mex(n, {0});
        std::map<uint64, uint64> add;

        uint64 sum = 0;

        for (uint64 i = 0; i < n; ++i)
        {
            uint64 l;
            std::cin >> l;

            v[i].resize(l);

            for (uint64 j = 0; j < l; ++j)
            {
                std::cin >> v[i][j];
            }

            std::ranges::sort(v[i]);

            for (uint64 j = 0; j < l and mex[i].size() <= 2; ++j)
            {
                if (v[i][j] == mex[i].back())
                {
                    ++mex[i].back();
                }
                else if (v[i][j] > mex[i].back())
                {
                    mex[i].push_back(mex[i].back() + 1);

                    if (v[i][j] == mex[i].back())
                    {
                        ++mex[i].back();
                    }
                    else
                    {
                        break;
                    }
                }
            }

            if (mex[i].size() == 1)
            {
                mex[i].push_back(mex[i].back() + 1);
            }

            add[mex[i][0]] += mex[i][1] - mex[i][0];
            sum += mex[i][0];
        }

        auto is_unique = [&](uint64 i, uint64 j) -> bool
        {
            if (j - 1 >= 0 and v[i][j] == v[i][j - 1])
            {
                return false;
            }

            if (j + 1 < v[i].size() and v[i][j] == v[i][j + 1])
            {
                return false;
            }

            return true;
        };

        uint64 ans = 0;

        for (uint64 i = 0; i < n; ++i)
        {
            for (uint64 j = 0; j < v[i].size(); ++j)
            {
                uint64 cmex = mex[i][0];
                uint64 csum = sum;

                if (v[i][j] < cmex and is_unique(i, j))
                {
                    csum -= cmex;
                    cmex = v[i][j];
                    csum += cmex;
                }

                ans += csum * (n - 1) + add[v[i][j]];
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}