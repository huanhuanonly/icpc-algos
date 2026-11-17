/**
 * AtCoder Beginner Contest 469
 *
 * => E - Pro Exam Eligibility ( @c 475 )
 *
 * -> https://atcoder.jp/contests/abc469/tasks/abc469_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc469/submissions/78131005 By huanhuanonly
 *
 * @b Binary-search
 * @b Probability-theory
 *
 * ----August 05, 2026 [16h:41m:57s]----
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

    std::string s;
    std::cin >> s;

    auto check = [&](real80 p) -> bool
    {
        std::vector<real80> pre(n + 1);
        std::vector<real80> min(n + 1);

        std::vector<int> pos;

        for (int i = 1; i <= n; ++i)
        {
            pre[i] = pre[i - 1] + (s[i - 1] == 'o' ? 1 - p : -p);
            min[i] = std::min(min[i - 1], pre[i]);

            if (s[i - 1] == 'o')
            {
                pos.push_back(i);
            }

            if (pos.size() >= k and pre[i] > min[pos[pos.size() - k] - 1])
            {
                return true;
            }
        }

        return false;
    };

    constexpr real80 eps = 1e-15;

    real80 l = 0, r = 1.1, mid;

    while (r - l > eps)
    {
        mid = (l + r) / 2;

        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }

    std::cout << std::fixed << std::setprecision(15) << l << '\n';

    return 0;
}