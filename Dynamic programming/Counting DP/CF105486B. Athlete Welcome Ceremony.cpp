/**
 * 2024 ICPC Asia Chengdu Regional Contest (The 3rd Universal Cup. Stage 15: Chengdu)
 *
 * => B. Athlete Welcome Ceremony
 *
 * -> https://codeforces.com/gym/105486/problem/B
 *
 * Submissions ~> https://codeforces.com/gym/105486/submission/389236205 By huanhuanonly
 *
 * @b Counting-DP
 * @b Prefix-sum
 *
 * ----September 03, 2026 [10h:22m:10s]----
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

    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;

    std::array<int, 3> cnt{};

    for (const auto& c : s)
    {
        if (c != '?')
        {
            ++cnt[c - 'a'];
        }
    }

    s.insert(s.begin(), ' ');

    constexpr uint64 mod = 1e9 + 7;

    std::vector dp(n + 1, std::vector(n + 1, std::vector(n + 1, std::array<uint64, 3>{})));

    if (s[1] == '?')
    {
        dp[1][1][0][0] = 1;
        dp[1][0][1][1] = 1;
        dp[1][0][0][2] = 1;
    }
    else
    {
        dp[1][s[1] == 'a'][s[1] == 'b'][s[1] - 'a'] = 1;
    }

    for (int i = 2; i <= n; ++i)
    {
        for (int a = 0; a <= n; ++a)
        {
            for (int b = 0; b <= n; ++b)
            {
                if (a and (s[i] == 'a' or s[i] == '?'))
                {
                    dp[i][a][b][0] = (dp[i - 1][a - 1][b][1] + dp[i - 1][a - 1][b][2]) % mod;
                }

                if (b and (s[i] == 'b' or s[i] == '?'))
                {
                    dp[i][a][b][1] = (dp[i - 1][a][b - 1][0] + dp[i - 1][a][b - 1][2]) % mod;
                }

                if (s[i] == 'c' or s[i] == '?')
                {
                    dp[i][a][b][2] = (dp[i - 1][a][b][0] + dp[i - 1][a][b][1]) % mod;
                }
            }
        }
    }

    std::vector pre(n + 1, std::vector(n + 1, uint64{}));

    for (int a = 0; a <= n; ++a)
    {
        for (int b = 0; b <= n; ++b)
        {
            pre[a][b] = std::ranges::fold_left(dp.back()[a][b], 0, std::plus{}) % mod;
        }

        for (int b = 1; b <= n; ++b)
        {
            (pre[a][b] += pre[a][b - 1]) %= mod;
        }
    }

    auto presum = [&](int i, int l, int r) -> uint64
    {
        if (l > r)
        {
            return 0;
        }
        else
        {
            return (pre[i][r] + mod - (l ? pre[i][l - 1] : 0)) % mod;
        }
    };

    while (q--)
    {
        int x, y, z;
        std::cin >> x >> y >> z;

        x = std::min(x + cnt[0], n);
        y = std::min(y + cnt[1], n);
        z = std::min(z + cnt[2], n);

        uint64 sum = 0;

        for (int i = 0; i <= x; ++i)
        {
            (sum += presum(i, std::max(0, n - z - i), std::min(y, n - i))) %= mod;
        }

        std::cout << sum << '\n';
    }

    return 0;
}