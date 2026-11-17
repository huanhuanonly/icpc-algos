/**
 * Codeforces Round 920 (Div. 3)
 *
 * => F. Sum of Progression ( @c 1900 )
 *
 * -> https://codeforces.com/contest/1921/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/1921/submission/347209370 By huanhuanonly
 *
 * @b Sqrt-decomposition ( @a by-parameter )
 * @b Prefix-sum
 *
 * ----November 03, 2025 [15h:31m:24s]----
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
        int n, q;
        std::cin >> n >> q;

        std::vector<int64> v(n);

        for (int64& i : v)
        {
            std::cin >> i;
        }

        const int block_size = std::sqrt(n);

        // [s][d]
        std::vector dp(n + 1, std::vector<int64>(block_size + 1));
        std::vector ad(n + 1, std::vector<int64>(block_size + 1));

        for (int d = 1; d <= block_size; ++d)
        {
            for (int s = n - 1; s >= 0; --s)
            {
                dp[s][d] = ad[s][d] = v[s];

                if (s + d < n)
                {
                    dp[s][d] += dp[s + d][d] + ad[s + d][d];
                    ad[s][d] += ad[s + d][d];
                }
            }
        }

        while (q--)
        {
            int s, d, k;
            std::cin >> s >> d >> k;

            --s;

            const int t = s + d * (k - 1);

            int64 sum = 0;

            if (d < block_size)
            {
                sum = dp[s][d] - (dp[std::min(t + d, n)][d] + ad[std::min(t + d, n)][d] * k);
            }
            else for (int i = s, ck = 1; i <= t; i += d, ++ck)
            {
                sum += v[i] * ck;
            }

            std::cout << sum << ' ';
        }

        std::cout.put('\n');
    }

    return 0;
}