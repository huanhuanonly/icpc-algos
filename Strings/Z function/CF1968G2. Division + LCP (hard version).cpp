/**
 * Codeforces Round 943 (Div. 3)
 *
 * => G2. Division + LCP (hard version) ( @c 2200 )
 *
 * -> https://codeforces.com/contest/1968/problem/G2
 *
 * Submissions ~> https://codeforces.com/contest/1968/submission/260247339 By huanhuanonly
 *
 * @b Z-function
 * @b Binary-search
 * @b Sqrt-decomposition ( @a by-parameter )
 *
 * ----May 10, 2024 [20h:05m:46s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
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

int answer(int k, const std::vector<int>& z)
{
    auto check = [&](int mid) -> bool
    {
        int cnt = 0;

        for (int i = 0; i < z.size(); ++i)
        {
            if (z[i] >= mid)
            {
                ++cnt;
                i += mid - 1;
            }
        }

        return cnt >= k;
    };

    int l = 0, r = z.size() / k + 1, mid;

    while (r - l > 1)
    {
        mid = l + r >> 1;

        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    return l;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, l, r;
        std::cin >> n >> l >> r;

        std::string s;
        std::cin >> s;

        if (n == 1)
        {
            std::cout << 1 << '\n';
            continue;
        }

        std::vector<int> z(get_z(s));

        auto count = [&](int x) -> int
        {
            int cnt = 0;

            for (int i = 0; i < n; )
            {
                if (z[i] >= x)
                    i += x,
                    ++cnt;
                else
                    ++i;
            }

            return cnt;
        };

        std::vector<int> ans(n + 1);
        ans[1] = n;

        int sq = std::sqrt(n);

        for (int i = 1; i <= sq; ++i)
        {
            if (int cnt = count(i); cnt != 1)
                ans[cnt] = i;
            else
                break;
        }

        for (int i = n, mx = 0; i >= 1; --i)
        {
            mx = std::max(mx, ans[i]);
            ans[i] = mx;
        }

        for (; l <= r; ++l)
            if (l <= sq)
                std::cout << answer(l, z) << " \n"[l == r];
            else
                std::cout << ans[l] << " \n"[l == r];
    }

    return 0;
}