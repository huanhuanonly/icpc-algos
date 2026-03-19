/**
 * 牛客周赛 Round 101
 * 
 * => E-qcjj寄快递 ( @c 1300 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/113313/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78338829 By huanhuanonly
 * 
 * @b Ternary-search on real numbers to find the minimum of a unimodal function (decreasing then increasing)
 * 
 * ----July 20, 2025 [20h:26m:11s]----
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

    int n;
    std::cin >> n;

    std::vector<std::pair<double, double>> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i].first >> v[i].second;
    }

    std::vector<double> e(n - 1);

    for (int i = 0; i < n - 1; ++i)
    {
        e[i] = std::sqrt(std::pow(v[i].first - v[i + 1].first, 2) + std::pow(v[i].second - v[i + 1].second, 2));
    }

    double ans = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        auto f = [&](double k) -> double
        {
            return 2 * k + 2 * e[i] / std::pow(2.0, k);
        };

        constexpr double eps = 1e-12;

        double l = 0, r = 32, mid1, mid2;

        while (r - l > eps)
        {
            double t = (r - l) / 3;
            mid1 = l + t, mid2 = r - t;

            if (f(mid1) > f(mid2))
            {
                l = mid1;
            }
            else
            {
                r = mid2;
            }
        }

        ans += f(l);
    }

    std::cout << std::fixed << std::setprecision(12) << ans;

    return 0;
}