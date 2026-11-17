/**
 * Codeforces Round 943 (Div. 3)
 *
 * => G1. Division + LCP (easy version) ( @c 1900 )
 *
 * -> https://codeforces.com/contest/1968/problem/G1
 *
 * Submissions ~> https://codeforces.com/contest/1968/submission/259481655 By huanhuanonly
 *
 * @b Z-function
 * @b Binary-search
 *
 * ----May 04, 2024 [17h:05m:16s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
using ldouble = long double;

std::vector<int> get_z(const std::string_view& s)
{
    std::vector<int> z(s.size());

    z[0] = s.size();

    int l = -1, r = 0;

    for (int i = 1; i < s.size(); ++i)
    {
        if (i <= r)
            z[i] = std::min(z[i - l], r - i + 1);

        while (i + z[i] < s.size() and s[z[i]] == s[i + z[i]])
            ++z[i];

        if (i + z[i] - 1 > r)
        {
            r = i + z[i] - 1;
            l = i;
        }
    }

    return z;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, k;
        std::string s;
        std::cin >> n >> k >> k >> s;

        std::vector<int> z(get_z(s));

        auto check = [&](int mid) -> bool
        {
            int cnt = 0;

            for (int i = 0; i < s.size(); ++i)
            {
                if (z[i] >= mid)
                {
                    ++cnt;
                    i += mid - 1;
                }
            }

            return cnt >= k;
        };

        int l = 0, r = s.size() + 1, mid;

        while (r - l > 1)
        {
            mid = l + r >> 1;

            if (check(mid))
                l = mid;
            else
                r = mid;
        }

        std::cout << l << '\n';
    }

    return 0;
}