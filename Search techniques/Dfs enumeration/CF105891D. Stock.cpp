/**
 * The 13th Shaanxi Provincial Collegiate Programming Contest
 * 
 * => D. Stock
 * 
 * -> https://codeforces.com/gym/105891/problem/D
 * 
 * Submissions ~> https://codeforces.com/gym/105891/submission/320006370 By huanhuanonly
 * 
 * @b Dfs-enumeration
 * 
 * ----May 17, 2025 [17h:19m:21s]----
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

    // Use read128 to get TLE
    using real = real64;

    real n, v;
    std::cin >> n >> v;

    std::vector<real> add, mul;

    for (int i = 0; i < n; ++i)
    {
        char opt;
        real x;

        std::cin >> opt >> x;

        if (opt == '+')
            add.push_back(x);
        else
            mul.push_back(x);
    }

    std::ranges::sort(add, std::greater());
    std::ranges::sort(mul, std::greater());

    int i = 0, j = 0;

    real ans = 0;

    auto dfs = [&](const auto& self, real sum, real last) -> void
    {
        if (i == add.size() and j == mul.size())
        {
            ans = std::max(ans, sum / n);
            return;
        }

        if (i < add.size())
        {
            ++i;
            self(self, sum + last + add[i - 1], last + add[i - 1]);
            --i;
        }
        
        if (j < mul.size())
        {
            ++j;
            self(self, sum + last * mul[j - 1], last * mul[j - 1]);
            --j;
        }
    };

    dfs(dfs, 0, v);

    std::cout << std::fixed << std::setprecision(12) << ans;

    return 0;
}