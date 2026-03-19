/**
 * Codeforces Round 1086 (Div. 2)
 * 
 * => E. Counting Cute Arrays ( @c Rating )
 * 
 * -> https://codeforces.com/contest/2208/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2208/submission/367261198 By huanhuanonly
 * 
 * @b DP on @b Bracket-tree
 * @b Monotonic-stack
 * @b Prefix-sum
 * 
 * ----March 19, 2026 [01h:07m:05s]----
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

        std::vector<int> v(n + 2);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
        }

        constexpr uint64 mod = 998244353;

        uint64 ans = 1;

        std::vector<int> maxr(n + 2);

        auto calc = [&](int l, int r) -> void
        {
            std::vector<uint64> dp(r - l + 1 + 1);
            std::vector<uint64> sum(r - l + 1 + 1);

            dp[0] = sum[0] = 1;

            for (int i = l, cnt = 1; ; ++cnt)
            {
                if (maxr[i])
                {
                    if ((i = maxr[i]) > r)
                    {
                        break;
                    }
                    
                    for (int j = cnt; j >= 1; --j)
                    {
                        dp[j] = dp[j - 1] % mod;
                    }
                }
                else
                {
                    if (++i > r)
                    {
                        break;
                    }

                    for (int j = 1; j <= cnt; ++j)
                    {
                        dp[j] = sum[j - 1] % mod;
                    }
                }

                dp[0] = 0;
                std::partial_sum(dp.rbegin(), dp.rend(), sum.rbegin());
            }

            (ans *= sum.front() % mod) %= mod;
        };

        std::stack<int> stack;
        stack.push(0);

        bool yes = true;

        for (int i = 1; i <= n + 1; ++i)
        {
            if (v[i] != -1)
            {
                for (; not stack.empty() and stack.top() != v[i]; stack.pop());

                if (stack.empty())
                {
                    yes = false;
                    break;
                }

                calc(v[i], i - 1);
                maxr[v[i]] = i;
            }

            stack.push(i);
        }

        if (yes)
        {
            std::cout << ans << '\n';
        }
        else
        {
            std::cout << 0 << '\n';
        }
    }

    return 0;
}