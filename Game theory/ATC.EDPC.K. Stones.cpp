/**
 * Educational DP Contest
 * 
 * => K - Stones ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_k
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/74988877 By huanhuanonly
 * 
 * @b Game-theory and @b Linear-DP
 * 
 * ----April 16, 2026 [09h:08m:35s]----
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

    int n, k;
    std::cin >> n >> k;

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    std::vector<bool> dp(k + 1);

    for (int i = v.front(); i <= k; ++i)
    {
        for (const int& j : v | std::views::take_while([i](int j) -> bool { return j <= i; }))
        {
            dp[i] = dp[i] or not dp[i - j];
        }
    }

    if (dp.back())
    {
        std::cout << "First\n";
    }
    else
    {
        std::cout << "Second\n";
    }

    return 0;
}