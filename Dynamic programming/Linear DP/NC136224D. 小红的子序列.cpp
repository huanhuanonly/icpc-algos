/**
 * 牛客周赛 Round 147
 *
 * => D-小红的子序列 ( @c 1500 )
 *
 * -> https://ac.nowcoder.com/acm/contest/136224/D
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83820221 By huanhuanonly
 *
 * @b Linear-DP and @b Number-theory ( @a prime-factorization )
 *
 * ----June 08, 2026 [08h:57m:27s]----
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

inline namespace huanhuanonly {
    inline namespace math
{
template<typename _Tp>
[[nodiscard]] std::vector<_Tp>
prime_factorization(_Tp __n, bool __unique = false)
{
    std::vector<_Tp> res;

    if (__unique)
    {
        for (_Tp i = 2; i * i <= __n; ++i)
        {
            if (__n % i == 0)
            {
                res.push_back(i);
                for (__n /= i; __n % i == 0; __n /= i);
            }

        }
    }
    else
    {
        for (_Tp i = 2; i * i <= __n; ++i)
        {
            for (; __n % i == 0; __n /= i)
            {
                res.push_back(i);
            }
        }
    }

    if (__n != 1)
    {
        res.push_back(__n);
    }

    return res;
}
}} // namespace huanhuanonly::math

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n;
    std::cin >> n;

    std::vector<int> v(n);
    std::map<int, std::vector<int>> pos;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
        pos[v[i]].push_back(i);
    }

    std::vector<int> dp(n, 1);
    std::vector<int> next(n, n);

    for (int i = n - 1; i >= 0; --i)
    {
        pos[v[i]].pop_back();

        for (int p : prime_factorization(v[i], true))
        {
            if (not pos[v[i] / p].empty() and dp[pos[v[i] / p].back()] < dp[i] + 1)
            {
                dp[pos[v[i] / p].back()] = dp[i] + 1;
                next[pos[v[i] / p].back()] = i;
            }
        }
    }

    const auto mpos = std::ranges::max_element(dp) - dp.begin();

    std::cout << dp[mpos] << '\n';

    for (int i = mpos; i < n; i = next[i])
    {
        std::cout << v[i] << ' ';
    }

    return 0;
}