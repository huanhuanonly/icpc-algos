/**
 * AtCoder Beginner Contest 461
 *
 * => F - Total Product is N ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc461/tasks/abc461_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc461/submissions/77470755 By huanhuanonly
 *
 * @b Number-theory ( @a divisor )
 * @b Combinatorics
 * @b Counting-DP
 *
 * ----July 14, 2026 [01h:27m:40s]----
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

    constexpr uint64 mod = 998244353;

    std::array<uint64, 16> fact;
    fact[0] = fact[1] = 1;

    for (uint64 i = 2; i < fact.size(); ++i)
    {
        fact[i] = fact[i - 1] * i % mod;
    }

    uint64 n;
    std::cin >> n;

    std::vector<uint64> ds;

    for (uint64 i = 1, sq = std::sqrt(n); i <= sq; ++i)
    {
        if (n % i == 0)
        {
            ds.push_back(i);
            ds.push_back(n / i);
        }
    }

    std::swap(ds.front(), ds.back());
    ds.pop_back();

    std::ranges::sort(ds);
    ds.erase(std::ranges::unique(ds).begin(), ds.end());

    std::unordered_map<uint64, std::array<uint64, 15>> dp, sum;
    dp[1][0] = 1;

    for (const uint64& d : ds)
    {
        auto s = sum;

        for (const auto& [key, value] : decltype(dp)(dp))
        {
            if (uint128(key) * d <= n and n % (key * d) == 0)
            {
                for (int i = 0; i < value.size() - 1; ++i)
                {
                    if (value[i])
                    {
                        (dp[key * d][i + 1] += value[i]) %= mod;
                        (sum[key * d][i + 1] += s[key][i] + d % mod * value[i]) %= mod;
                    }
                }
            }
        }
    }

    uint64 ans = 0;

    const auto& dpn = dp[n];
    const auto& sumn = sum[n];

    for (int i = 1; i < dpn.size(); ++i)
    {
        ans += fact[i] * sumn[i] % mod;
    }

    if (n > 1)
    {
        for (int i = 1; i < dpn.size(); ++i)
        {
            ans += fact[i + 1] * ((sumn[i] + dpn[i]) % mod) % mod;
        }
    }

    std::cout << ans % mod << '\n';

    return 0;
}