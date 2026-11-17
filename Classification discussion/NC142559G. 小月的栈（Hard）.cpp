/**
 * 牛客周赛 Round 168
 *
 * => G-小月的栈（Hard） ( @c 1700 )
 *
 * -> https://ac.nowcoder.com/acm/contest/142559/G
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=85353845 By huanhuanonly
 *
 * @b Classification-discussion
 *
 * ----November 02, 2026 [01h:08m:43s]----
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

        std::vector<std::pair<int, bool>> a(n), b(m);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> a[i].first >> a[i].second;
        }

        for (int i = 0; i < m; ++i)
        {
            std::cin >> b[i].first >> b[i].second;
        }

        constexpr auto inf = std::numeric_limits<int64>::min() / 2;

        int64 ans = inf;
        int64 sum = 0;

        std::array<std::array<int, 2>, 2> cnt{};
        std::array<bool, 2> end_with_1{};

        auto check = [&]() -> bool
        {
            if (cnt[0][0] + cnt[0][1] + cnt[1][0] + cnt[1][1] != k)
            {
                return false;
            }

            if (cnt[0][1] <= cnt[1][1])
            {
                return cnt[0][1] + cnt[0][0] >= cnt[1][1] - end_with_1[1];
            }
            else
            {
                return cnt[1][1] + cnt[1][0] >= cnt[0][1] - end_with_1[0];
            }
        };

        for (int i = 0, e = std::min(m, k); i < e; ++i)
        {
            ++cnt[1][b[i].second];
            sum += b[i].first;
        }

        end_with_1[1] = b[std::min(m, k) - 1].second;

        if (check())
        {
            ans = sum;
        }

        for (int i = 0, e = std::min(n, k); i < e; ++i)
        {
            ++cnt[0][a[i].second];
            sum += a[i].first;

            end_with_1[0] = a[i].second;

            if (const int j = k - i - 1; 0 <= j and j < m)
            {
                --cnt[1][b[j].second];
                sum -= b[j].first;

                end_with_1[1] = j ? b[j - 1].second : false;
            }

            if (check())
            {
                ans = std::max(ans, sum);
            }
        }

        if (ans != inf)
        {
            std::cout << ans << '\n';
        }
        else
        {
            std::cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}