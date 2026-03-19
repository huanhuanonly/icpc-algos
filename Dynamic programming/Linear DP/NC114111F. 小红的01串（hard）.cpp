/**
 * 牛客周赛 Round 102
 * 
 * => 小红的01串（hard） ( @c 1800 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/114111/F
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78496714 By huanhuanonly
 * 
 * @b Linear-DP
 * 
 * ----July 27, 2025 [21h:17m:05s]----
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

    std::vector<int> v(1);
    v.reserve(1000);

    for (int i = 1; v.back() < 2e5; ++i)
    {
        v.push_back(v.back() + i);
    }

    constexpr int inf = std::numeric_limits<int>::max() / 2;

    std::vector<int> dp(2e5 + 1, inf);
    std::vector<int> last(dp.size(), inf);

    for (int i = 1; i < v.size(); ++i)
    {
        dp[v[i]] = i;
    }

    for (int i = 1; i < dp.size(); ++i)
    {
        for (int j = 1; j < v.size() and i + v[j] < dp.size(); ++j)
        {
            if (dp[i + v[j]] > dp[i] + 1 + j)
            {
                dp[i + v[j]] = dp[i] + 1 + j;
                last[i + v[j]] = j;
            }
        }
    }

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        int cur = n;

        for (; last[cur] != inf; cur -= v[last[cur]])
        {
            std::cout << std::string(last[cur], '1');
            std::cout.put('0');
        }

        std::cout << std::string(dp[cur], '1');
        std::cout.put('\n');
    }

    return 0;
}